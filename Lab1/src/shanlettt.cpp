set flag=0
:: ******�жϴ���������Ƿ�򿪣��������ر�
reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" | find /i "proxyserver" >nul && (
    reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v ProxyEnable /t REG_DWORD /d 0 /f >nul
    :: echo �����ѹر�
) || (
    :: echo ����δ����
)

:: *****�ж�wps.exe�ĸ����Ƿ�С��4����һ���ļ������4���Ʒ���ռ3����
for /f %%i in ('tasklist /fi "imagename eq wps.exe" ^| find /i /c "wps.exe"') do set flag=%%i
if %flag% LSS 4 (
    ::shutdown -s -t 0
    echo WPS�ѹر�
    pause
) else (
    echo WPSδ�رգ����ȹر�WPS��
    pause
)