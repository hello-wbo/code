/*---------------------------------------
   BITBLT.C -- BitBlt Demonstration
               (c) Charles Petzold, 1998
  ---------------------------------------*/

#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName [] = TEXT ("BitBlt") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_INFORMATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

     hwnd = CreateWindow (szAppName, TEXT ("BitBlt Demo"), 
                          WS_OVERLAPPEDWINDOW, 
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;

     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static int  cxClient, cyClient, cxSource, cySource ;
     HDC         hdcClient, hdcWindow ;
     int         x, y ;
     PAINTSTRUCT ps ;

     switch (message)
     {
     case WM_CREATE:
          cxSource = GetSystemMetrics (SM_CXSIZEFRAME) +
                     GetSystemMetrics (SM_CXSIZE) ;

          cySource = GetSystemMetrics (SM_CYSIZEFRAME) + 
                     GetSystemMetrics (SM_CYCAPTION) ;
          return 0 ;

     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;

     case WM_PAINT:
          hdcClient = BeginPaint (hwnd, &ps) ;
          hdcWindow = GetWindowDC (hwnd) ;

          for (y = 0 ; y < cyClient ; y += cySource)
          for (x = 0 ; x < cxClient ; x += cxSource)
          {
               BitBlt (hdcClient, x, y, cxSource, cySource,
                       hdcWindow, 0, 0, SRCCOPY) ;
          }

          ReleaseDC (hwnd, hdcWindow) ;
          EndPaint (hwnd, &ps) ;
          return 0 ;
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

case WM_PAINT:
{
     PAINTSTRUCT ps;
     HDC hdc = BeginPaint(hWnd, &ps);
     // TODO: 在此处添加使用 hdc 的任何绘图代码...

     HBITMAP hbmp;                      // 位图绘制对象句柄
     HDC mdc = CreateCompatibleDC(hdc); // 创建兼容的缓存DC对象

     // 加载图片到位图绘制对象hbmp中
     hbmp = (HBITMAP)LoadImage(
         NULL,                       // 模块实例句柄
         "K:\\dcm_picture\\111.bmp", // 位图路径。 注意双斜杠，单斜杠表示转义，此时文件会加载不成功！！！
         IMAGE_BITMAP,               // 图片类型
         WINDOW_WIDTH,               // 指定图片宽
         WINDOW_HEIGHT,              // 指定图片高
         LR_LOADFROMFILE             // 从路径处加载图片
     );

     // 缓存DC（mdc）选择位图绘制对象（可以理解为将图片保存到mdc中）
     SelectObject(mdc, hbmp);

     // 将缓存DC中的位图复制到窗口DC上
     BitBlt(
         hdc,           // 目的DC
         0, 0,          // 目的DC的 x，y 坐标
         WINDOW_WIDTH,  // 要粘贴的图片的宽
         WINDOW_HEIGHT, // 要粘贴的图片的高
         mdc,           // 缓存DC
         0, 0,          // 缓存DC的x，y坐标
         SRCCOPY        // 粘贴方式
     );
     DeleteObject(hbmp);
     DeleteDC(mdc);
     EndPaint(hWnd, &ps);
}