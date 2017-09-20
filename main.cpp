#include <windows.h>
#include <vulkan/vulkan.h>

#include <cassert>

namespace
{
	const auto kWindowClassName = TEXT( "VulkanTest" );
	const auto kWindowName		= TEXT( "VulkanTest" );
}

static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int main()
{
	//----------------------------------------------------
	// インスタンスハンドルを取得.
	HINSTANCE hInstance = GetModuleHandle( nullptr );
	if ( !hInstance )
	{
		// TODO: エラー処理.
		assert( 0 );
	}

	WNDCLASSEX wce{};
	wce.cbSize			= sizeof wce;
	wce.hInstance		= hInstance;
	wce.lpszClassName	= kWindowClassName;
	wce.lpfnWndProc		= &WndProc;
	wce.style			= CS_OWNDC;
	wce.hCursor			= LoadCursor( nullptr, IDC_ARROW );
	if( !RegisterClassEx( &wce ) )
	{
		// TODO: エラー処理.
		assert( 0 );
	}

	// ウィンドウハンドル作成.
	RECT rc;
	SetRect( &rc, 0, 0, 640, 480 );
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, false, 0);
	HWND hWnd	= CreateWindowEx(0, wce.lpszClassName, kWindowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	if( !hWnd )
	{
		// TODO: エラー処理.
		assert( 0 );
	}

	//----------------------------------------------------
    // ウィンドウを表示.
    ShowWindow( hWnd, SW_SHOWNORMAL );
	
	MSG msg;
	while( GetMessage( &msg, nullptr, 0, 0 ) > 0 )
	{
		DispatchMessage( &msg );
	}

	return 0;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}
		case WM_PAINT:
		{
			return 0;
		}
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
