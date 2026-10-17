"""Run the original ActivityInfo consumer against a synthetic JNI table."""
import json,struct
from device_fixture import *
from unicorn.arm64_const import UC_ARM64_REG_X3
ENV=DATA+0x1000;TABLE=DATA+0x2000;STUB=DATA+0x4000
class ActivityFixture(DeviceFixture):
    def __init__(self):
        super().__init__()
        self.handlers[0x3b3440]=lambda f:f.return_value(self.obj('Application'))
        for slot in range(240):self.handlers[STUB+slot*4]=lambda f,s=slot:f.jni(s)
    def obj(self,kind,value=None):
        p=self.allocate(8);self.objects[p]=(kind,value);return p
    def jni(self,slot):
        a=[self.uc.reg_read(r) for r in (UC_ARM64_REG_X0,UC_ARM64_REG_X1,UC_ARM64_REG_X2,UC_ARM64_REG_X3)]
        assert a[0]==ENV
        value=0;trace=dict(slot=slot)
        if slot in (15,17,228,22,23,170):pass
        elif slot in (21,25):value=a[1]
        elif slot==6:value=self.obj('class',self.cstring(a[1]).decode());trace['class']=self.objects[value][1]
        elif slot==31:value=self.obj('class',self.objects[a[1]][0])
        elif slot in (33,94):
            name=self.cstring(a[2]).decode();sig=self.cstring(a[3]).decode();value=self.obj('member',name);trace.update(name=name,signature=sig)
        elif slot==35:
            name=self.objects[a[2]][1];trace['method']=name
            if name=='getPackageManager':value=self.obj('PackageManager')
            elif name=='getPackageName':value=self.obj('string','APP_PACKAGE')
            elif name=='getPackageInfo':value=self.obj('PackageInfo')
            else:raise ValueError(name)
        elif slot==95:
            name=self.objects[a[2]][1];trace['field']=name
            if name=='activities':value=self.obj('array',self.names)
            elif name=='name':value=self.obj('string',self.objects[a[1]][1])
            else:raise ValueError(name)
        elif slot==171:value=len(self.objects[a[1]][1])
        elif slot==173:value=self.obj('ActivityInfo',self.objects[a[1]][1][a[2]])
        elif slot==168:value=len(self.objects[a[1]][1].encode())
        elif slot==169:
            v=self.objects[a[1]][1].encode();value=self.allocate(len(v)+1);self.uc.mem_write(value,v+b'\0')
        else:
            self.reason='unmodeled_JNI_slot:'+str(slot);self.uc.emu_stop();return
        self.trace.append(trace);self.return_value(value)
    def probe(self,names):
        self.reset();self.objects={};self.trace=[];self.names=names
        self.uc.mem_write(ENV,struct.pack('<Q',TABLE))
        for s in range(240):self.uc.mem_write(TABLE+s*8,struct.pack('<Q',STUB+s*4))
        r=self.call(0x37fb88,[ENV],DATA+0x5000)
        result=[self.get_string(DATA+0x5000).decode(),bool(self.uc.mem_read(DATA+0x5018,1)[0])] if r['reason']=='returned' else None
        return dict(names=names,result=result,run=r,JNI_trace=self.trace,modeled_boundaries=sorted(self.modeled|{'synthetic_JNI_table','application_getter'}))
if __name__=='__main__':
    f=ActivityFixture();rows=[]
    cases=[[],['com.example.Main'],['com.example.wxapi.WXEntryActivity'],['com.netease.mpay.MpayLoginActionBarActivity'],['foo.wxapi.WXEntryActivity.extra'],['com.netease.mpay.MpayLoginActionBarActivity.extra'],['foo.wxapi.WXEntryActivity.extra','bar.wxapi.WXEntryActivity','com.netease.mpay.MpayLoginActionBarActivity']]
    for v in cases:
        r=f.probe(v);rows.append(r);print(v,r['run']['reason'],r['result'],r['JNI_trace'],flush=True)
        (OUT/'evidence/activity-original.json').write_text(json.dumps(rows,indent=2))
        if r['run']['reason']!='returned':break
