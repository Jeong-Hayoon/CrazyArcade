﻿// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "framework.h"
#include "Client.h"
#include "hyApplication.h"
#include "hySceneManager.h"
    
#include "hyTexture.h"
#include "hyResources.h"
#include "hyInput.h"
#include "hyTile.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                         // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];           // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];     // 기본 창 클래스 이름입니다.
extern hy::Application application = {};

ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndToolProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 메모리 릭 해제
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(465);
    
    //Gdiplus::GdiplusStartup

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance, szWindowClass, WndProc);
    MyRegisterClass(hInstance, L"Tool", WndToolProc);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow)) // 윈도우가 만들어져서 화면에 그려짐
    {
        return FALSE;
    }

    // 커서 설정하는 부분
    LPCWSTR CrazyArcadeCursor = L"..\\Resources\\Image\\Mouse\\mouse.cur";

    // 커서 핸들 생성
    HCURSOR hCursor = LoadCursorFromFile(CrazyArcadeCursor);

    SetCursor(hCursor);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // GetMessage : 프로세스에 발생한 메시지를 메세지큐에서 꺼내옴
    //              (msg.message == WM_QUIT) return false;
    //              WM_QUIT 이외의 메세지가 발생 한 경우는 return true; 

    // PeekMessage : 프로세스에 발생한 메시지를 메세지큐에서 꺼내옴
    //               PM_REMOVE -> 발생한 메세지를 가져올 때 메세지큐에서 제거 (GetMessage 랑 동일하게 하기 위해서...)
    //               메세지큐에 메세지 유/무 에 상관없이 함수가 리턴됨
    //               리턴값이 true 인 경우 메세지가 있었다. 리턴값이 false 인 경우 메세지가 큐에 없었다.

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 메세지가 있으면
        {
            if (WM_QUIT == msg.message) // 메세지가 종료하는 메세지면 반복문을 나가서 종료
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else // 메세지가 없으면 게임 실행
        {
            SetCursor(hCursor);

            application.Run();
        }
    }

    if (msg.message == WM_QUIT)  // 동적할당한 부분들 해제
    {
        
    }

    // 메모리 해제
    application.Release();
    hy::SceneManager::Release();
    hy::Resources::Release();
    Gdiplus::GdiplusShutdown(gdiplusToken);
    DestroyCursor(hCursor);

    return (int) msg.wParam;        
}


//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex = {};  

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;      // 윈도우 스타일
    wcex.lpfnWndProc /*(callback 함수 포인터 : 운영체제에서 호출하는 함수)*/ = proc;     // 실행시킬 함수
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT)); // 아이콘(리소스 뷰)
    wcex.hCursor        = NULL;                                              // 커서 모양
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                         // 백그라운드 색상
    wcex.lpszMenuName   = nullptr;                                          // 메뉴 이름
    wcex.lpszClassName  = name;                                    // 등록할 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, //WS_OVERLAPPEDWINDOW : 윈도우 창 스타일,
      0, 0, 800, 600, nullptr, nullptr, hInstance, nullptr); // 윈도우 생성 시 WndProc 함수 호출

   HWND hWndTool = CreateWindowW(L"Tool", szTitle, WS_OVERLAPPEDWINDOW,
       0, 0, 200, 200, nullptr, nullptr, hInstance, nullptr);
   
   // 핸들에는 만들어진 윈도우 정보에 대한 시작 주소가 반환되어 들어감(핸들은 포인터)
   // 우리는 핸들을 통해 데이터 접근을 하게 됨

   // Gdiplus 초기화
   Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   application.Initialize(hWnd);

   if (!hWnd) // null이라면 실패한 것 -> 프로그램 종료(? 근데 왜!hWnd가 의미하는 것이 hWnd가 null이라면으로 해석이 되는지 )
   {
      return FALSE;
   }

   // main
   ShowWindow(hWnd, nCmdShow);      // 윈도우를 보여주는 함수
   UpdateWindow(hWnd);              // 윈도우가 돌아가게끔 실행시켜 주는 함수

   /// tool
   RECT rect = { 0, 0, 200, 200 };
   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
   SetWindowPos(hWndTool
       , nullptr, 1000, 0
       , rect.right - rect.left
       , rect.bottom - rect.top
       , 0);
   ShowWindow(hWndTool, nCmdShow);
   UpdateWindow(hWndTool);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND: //soen 메세지 종류 참고
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); //DC는 윈도우에서 그림과 관련된 작업을 해주는 영역
            // 그 영역의 시작주소를 넣어주는 과정(HDC도 포인터)
            
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndToolProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;


    // 마우스 왼쪽 버튼을 누르면 커서의 정보를 가져와서 좌표를 저장
    case WM_LBUTTONDOWN:
    {
        POINT mousePos = {};
        // 마우스 커서 위치 정보를 가져오는 함수
        GetCursorPos(&mousePos);
        // 위의 메뉴바를 빼고 좌표를 구할 수 있도록 해주는 함수
        ScreenToClient(hWnd, &mousePos);

        int idxX = mousePos.x / (TILE_WIDTH);
        int idxY = mousePos.y / (TILE_HEIGHT);

        hy::Tile::mSelectedX = idxX;
        hy::Tile::mSelectedY = idxY;
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //Rectangle(hdc, 0, 0, 100, 100);
        //여기서 이미지 를 그려준다.

        // 타일 주석
        hy::Texture* Tile_
           = hy::Resources::Find<hy::Texture>(L"Tile");

        TransparentBlt(hdc  
           , 0, 0, Tile_->GetWidth(), Tile_->GetHeight()
           , Tile_->GetHdc()
          , 0, 0, Tile_->GetWidth(), Tile_->GetHeight()
           , RGB(255, 0, 255));

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
