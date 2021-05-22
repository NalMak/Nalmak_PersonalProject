del ..\..\..\Ref\Include\*.h
xcopy /y ..\Include\*.h ..\..\..\Ref\Include\
xcopy /y ..\Bin\*.dll ..\..\..\Client\Bin\Win32\Debug\
xcopy /y ..\Bin\*.dll ..\..\..\Client\Bin\Win32\Release\
xcopy /y ..\Bin\*.dll ..\..\..\Client\Bin\x64\Debug\
xcopy /y ..\Bin\*.dll ..\..\..\Client\Bin\x64\Release\


xcopy /y ..\Bin\*.lib ..\..\..\Ref\Lib\
xcopy /y ..\Bin\*.cso ..\..\..\Ref\ShaderCompiled\

xcopy /y ..\Bin\*.dll ..\..\EffectTool\
xcopy /y ..\Bin\*.dll ..\..\MapTool\
xcopy /y ..\Bin\*.dll ..\..\BoneAnimationTool\
xcopy /y ..\Bin\*.dll ..\..\AnimationTool\