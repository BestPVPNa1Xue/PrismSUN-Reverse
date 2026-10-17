"""Validate only the accessibility checker's initializer, factory and methods.

The generic registry singleton and registry insertion are fixture boundaries;
no scheduler, network or other checker is executed.
"""
import json
import struct
from hash_original import HashFixture, ROOT, DATA, REGISTERS, UC_ARM64_REG_X8

fixture = HashFixture()
fixture.reset()
captures = []


def registry_insert(f):
    registry, key, callback = [f.uc.reg_read(r) for r in REGISTERS[:3]]
    raw = bytes(f.uc.mem_read(callback, 40))
    body = struct.unpack("<Q", raw[32:40])[0]
    vtable = struct.unpack("<Q", f.uc.mem_read(body, 8))[0]
    invoke = struct.unpack("<Q", f.uc.mem_read(vtable + 48, 8))[0]
    captures.append({"registry": hex(registry), "key": key,
                     "callback_raw": raw.hex(), "body": hex(body),
                     "vtable": hex(vtable), "invoke": hex(invoke)})
    f.return_value(0)


fixture.handlers[0x4EA8B8] = lambda f: f.return_value(DATA + 0x1000)
fixture.handlers[0x601C58] = registry_insert
registration = fixture.run(0x6B6F3C, [], count=500000, timeout_us=10_000_000)
assert registration["reason"] == "returned", registration
assert len(captures) == 1 and captures[0]["key"] == 38, captures
assert captures[0]["vtable"] == "0x793da0"

# Recreate the empty callback object at a persistent fixture address; then call
# its original invoke method to get the real checker constructed by the binary.
fixture.reset()
fixture.uc.mem_write(DATA, struct.pack("<QQ", 0x793DA0, 0))
fixture.uc.reg_write(UC_ARM64_REG_X8, DATA + 0x8000)
factory = fixture.run(0x6BB444, [DATA], count=500000, timeout_us=10_000_000)
pointer = struct.unpack("<Q", fixture.uc.mem_read(DATA + 0x8000, 8))[0]
vtable = struct.unpack("<Q", fixture.uc.mem_read(pointer, 8))[0]
assert factory["reason"] == "returned", factory
assert vtable == 0x793DE8

constants = []
for address, expected in [(0x6CDFB4, 38), (0x6CE3EC, 1), (0x631408, 0), (0x6CE880, 1)]:
    fixture.reset()
    result = fixture.run(address, [DATA])
    assert result["reason"] == "returned" and result["return"] == expected, result
    constants.append(result)

completed_queries = []
fixture.handlers[0x3B8C40] = lambda f: f.return_value(DATA + 0x1000)
for initialized in (0, 1):
    fixture.reset()
    fixture.uc.mem_write(DATA + 0x1000 + 556, bytes([initialized]))
    result = fixture.run(0x6CFA68, [DATA])
    assert result["reason"] == "returned" and result["return"] == initialized, result
    completed_queries.append({"context_plus_556": initialized, "result": result})

forwarded = []
def observe_consumer(f):
    forwarded.append({"x0": hex(f.uc.reg_read(REGISTERS[0])),
                      "x1": hex(f.uc.reg_read(REGISTERS[1])),
                      "x8_result_buffer": hex(f.uc.reg_read(UC_ARM64_REG_X8))})
    f.return_value(0x1234)
fixture.handlers[0x6CF0C8] = observe_consumer
fixture.reset()
fixture.uc.mem_write(DATA, struct.pack("<Q", 0x793DE8))
fixture.uc.reg_write(UC_ARM64_REG_X8, DATA + 0x8000)
dispatch = fixture.run(0x6CF6D4, [DATA, DATA + 0x4000])
assert dispatch["reason"] == "returned" and dispatch["return"] == 0x1234
assert forwarded == [{"x0": hex(DATA), "x1": hex(DATA + 0x4000), "x8_result_buffer": hex(DATA + 0x8000)}]

evidence = {"scope": "AccessibilityServiceChecker only; generic registry insertion and singleton retrieval are modeled boundaries.",
            "registration": registration, "registry_calls": captures,
            "factory": factory, "checker_vtable": hex(vtable), "constant_methods": constants,
            "initialized_status_queries": completed_queries,
            "dispatch_wrapper": dispatch, "forwarded_arguments": forwarded,
            "not_established": "The units/semantics of vtable +0x20 and +0x30, concrete scheduler period, and external execution triggers are not inferred from constants."}
(ROOT / "evidence" / "hash-upstream-scheduling-emulation.json").write_text(json.dumps(evidence, indent=2), encoding="utf-8")
print("PASS: original initializer registers key 38; original factory creates vtable 0x793de8; method constants verified")
