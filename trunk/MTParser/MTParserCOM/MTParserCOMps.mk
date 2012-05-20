
MTParserCOMps.dll: dlldata.obj MTParserCOM_p.obj MTParserCOM_i.obj
	link /dll /out:MTParserCOMps.dll /def:MTParserCOMps.def /entry:DllMain dlldata.obj MTParserCOM_p.obj MTParserCOM_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MTParserCOMps.dll
	@del MTParserCOMps.lib
	@del MTParserCOMps.exp
	@del dlldata.obj
	@del MTParserCOM_p.obj
	@del MTParserCOM_i.obj
