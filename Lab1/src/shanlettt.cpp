set flag=0
:: ******判断代理服务器是否打开，如果打开则关闭
reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" | find /i "proxyserver" >nul && (
    reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyEnable /t REG_DWORD /d 0 /f >nul
    :: echo 代理已关闭
) || (
    :: echo 代理未开启
)

:: *****判断wps.exe的个数是否小于4（打开一个文件后等于4，云服务占3个）
for /f %%i in ('tasklist /fi "imagename eq wps.exe" ^| find /i /c "wps.exe"') do set flag=%%i
if %flag% LSS 4 (
    ::shutdown -s -t 0
    echo WPS已关闭
    pause
) else (
    echo WPS未关闭，请先关闭WPS。
    pause
)