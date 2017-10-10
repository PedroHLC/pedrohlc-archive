/*
###################################
#
# freergss.c Ver. 0.0.3
#
###################################
*/
#define FREERGSS_VERSION "0.0.3"

#undef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION        (0x0800)            /* DirectInputバージョン定義 */
#define WINVER 0x0500            //    バージョン定義 Windows2000以上
#define _WIN32_WINNT WINVER

#include "ruby.h"
#include <stdlib.h>
#include <mmsystem.h>
#include <tchar.h>
#include <d3dx9.h>
#include <dmusici.h>
#include <dinput.h>
#include <memory.h>
#include <math.h>

#ifndef RSTRING_PTR
#  define RSTRING_PTR(s) (RSTRING(s)->ptr)
#endif
#ifndef RSTRING_LEN
#  define RSTRING_LEN(s) (RSTRING(s)->len)
#endif

#ifndef RARRAY_PTR
#  define RARRAY_PTR(s) (RARRAY(s)->ptr)
#endif
#ifndef RARRAY_LEN
#  define RARRAY_LEN(s) (RARRAY(s)->len)
#endif

#define RELEASE( x )  if( x ) { x->lpVtbl->Release( x ); x = NULL; }

#define FR_CHECK_TYPE( a, b ) \
        {if( TYPE( b ) != T_DATA || RDATA( b )->dfree != (RUBY_DATA_FUNC)release_##a )\
        rb_raise(rb_eTypeError, "wrong argument type %s (expected FreeRGSS::"#a")", rb_obj_classname( b ));}

#define FR_IS_TRUE( x ) (x != Qnil && x != Qfalse)
#define FR_IS_FALSE( x ) (x == Qnil || x == Qfalse)
#define FR_GET_STRUCT( c, v ) ((struct FR_##c *)DATA_PTR( v ))
#define FR_MAX( a, b ) (a > b ? a : b)
#define FR_MIN( a, b ) (a > b ? b : a)
#define FR_0_255( a ) (a > 255 ? 255 : (a < 0) ? 0 : a)
#define FR_M255_255( a ) (a > 255 ? 255 : (a < -255) ? -255 : a)
#define FR_CHECK_BITMAP_DISPOSE( a ) {if( a->pD3DTexture == NULL ) { rb_raise( eFreeRGSSError, "disposed bitmap" );}}


#define PADMAX 2

#define P_LEFT     0
#define P_RIGHT    1
#define P_UP       2
#define P_DOWN     3
#define P_BUTTON0  4
#define P_BUTTON1  5
#define P_BUTTON2  6
#define P_BUTTON3  7
#define P_BUTTON4  8
#define P_BUTTON5  9
#define P_BUTTON6  10
#define P_BUTTON7  11
#define P_BUTTON8  12
#define P_BUTTON9  13
#define P_BUTTON10 14
#define P_BUTTON11 15
#define P_BUTTON12 16
#define P_BUTTON13 17
#define P_BUTTON14 18
#define P_BUTTON15 19
#define M_LBUTTON   0
#define M_RBUTTON   1
#define M_MBUTTON   2
#define FRB_DOWN    2
#define FRB_LEFT    4
#define FRB_RIGHT   6
#define FRB_UP      8
#define FRB_A       11
#define FRB_B       12
#define FRB_C       13
#define FRB_X       14
#define FRB_Y       15
#define FRB_Z       16
#define FRB_L       17
#define FRB_R       18
#define FRB_SHIFT   21
#define FRB_CTRL    22
#define FRB_ALT     23
#define FRB_F5      25
#define FRB_F6      26
#define FRB_F7      27
#define FRB_F8      28
#define FRB_F9      29



static VALUE cBitmap;       /* Bitmapクラス         */
static VALUE cSprite;       /* Spriteクラス         */
static VALUE cRect;         /* Rectクラス           */
static VALUE cTone;         /* Toneクラス           */
static VALUE cColor;        /* Colorクラス          */
static VALUE cViewport;     /* Viewportクラス       */
static VALUE cFont;         /* フォントクラス       */
static VALUE cPlane;        /* Planeクラス          */
static VALUE cTable;        /* Tableクラス          */
static VALUE cTilemap;      /* Tilemapクラス        */
static VALUE cWindow;       /* Windowクラス         */
static VALUE mGraphics;     /* Graphicsモジュール   */
static VALUE mInput;        /* インプットモジュール */
static VALUE mAudio;        /* Audioモジュール      */

static VALUE eFreeRGSSError;  /* 例外                 */

/* グローバル変数たち */
static HINSTANCE             g_hInstance   = NULL; /* アプリケーションインスタンス   */
static HANDLE                g_hWnd       = NULL; /* ウィンドウハンドル             */
static LPDIRECT3D9           g_pD3D        = NULL; /* Direct3Dインターフェイス       */
static LPDIRECT3DDEVICE9     g_pD3DDevice  = NULL; /* Direct3DDeviceインターフェイス */
static D3DPRESENT_PARAMETERS g_D3DPP;              /* D3DDeviceの設定                */
static LPD3DXSPRITE          g_pD3DXSprite = NULL; /* スプライト                     */

static LPDIRECTINPUT8        g_pDInput            = NULL; /* DirectInput */
static LPDIRECTINPUTDEVICE8  g_pDIDKeyBoard       = NULL; /* DirectInputのキーボードデバイス */
static LPDIRECTINPUTDEVICE8  g_pDIDJoyPad[PADMAX];        /* DirectInputのパッドデバイス     */
static BYTE g_diKeyState[256];                            /* DirectInputでのキーボード入力用バッファ */
static BYTE g_diKeyCount[256];                            /* DirectInputでのキーボード入力用カウンタ */
static BYTE g_diKeyConfig[256];                           /* DirectInputでのキーボード・パッド割り当て */
static BYTE g_diKeyWait[256];                             /* オートリピートウェイト時間 */
static BYTE g_diKeyInterval[256];                         /* オートリピート間隔 */
static int g_JoystickCount = 0;
static BYTE g_byMouseState_L, g_byMouseStateOld_L;
static BYTE g_byMouseState_M, g_byMouseStateOld_M;
static BYTE g_byMouseState_R, g_byMouseStateOld_R;

static BYTE g_fr_button[30];
static BYTE g_fr_button_count[30];
static BYTE g_fr_button_old[30];


static int g_iRefAll = 1; /* インターフェースの参照カウント */

/* ゲーム調整用 */
static int g_bActive = 0;

/* フレーム調整用 */
static __int64 g_OneSecondCount       = 0;         /* 一秒間にカウンタが数える数         */
static int     g_isPerformanceCounter = 0;         /* パフォーマンスカウンタがあったら１ */
static __int64 g_OldTime              = 0;         /* 前回のフレームが終わった時間       */
static __int64 g_OneFrameCount        = 0;         /* １フレームの処理にかかった時間     */
static __int64 g_DrawTime             = 0;         /* 描画にかかった時間                 */

/* ウィンドウ情報構造体 */
static struct FR_WindowInfo {
    int x;              /* ｘ座標 */
    int y;              /* ｙ座標 */
    int width;          /* 幅     */
    int height;         /* 高さ   */
    int windowed;       /* ウィンドウモード時にQtrue */
    int created;        /* ウィンドウを作成したらQtrue */
    float scale;        /* ウィンドウのサイズ倍率 */
    int RefreshRate;    /* リフレッシュレート */
    int enablemouse;    /* マウスを表示するかどうか */
    int mousewheelpos;  /* マウスホイールの位置 */
    int fps;            /* fps */
    int fpscheck;       /* 現在のfps */
    int frameskip;      /* コマ落ち制御フラグ */
    int r;              /* 背景クリア色 赤成分 */
    int g;              /* 背景クリア色 緑成分 */
    int b;              /* 背景クリア色 青成分 */
    int minfilter;      /* 縮小フィルタ */
    int magfilter;      /* 拡大フィルタ */
    HANDLE hIcon;       /* ウィンドウアイコンハンドル */
    int loop;           /* Window.loopされてたら1 */
    int requestclose;   /* ウィンドウが閉じられたら1 */
} g_WindowInfo;

LPD3DXEFFECT m_pEffect;
D3DXHANDLE m_hTechnique_sprite;
D3DXHANDLE m_hTechnique_viewport;
D3DXHANDLE g_hcolor_sprite;
D3DXHANDLE g_hcolor_viewport;
D3DXHANDLE g_htone_sprite;
D3DXHANDLE g_htone_viewport;

typedef struct tag_dx_TLVERTEX {
    float           x, y, z;
    D3DCOLOR        color;
    float           tu, tv;
}TLVERTX, *LPTLVERTEX;

struct FR_Graphics {
    VALUE vsprites;
    int frame_count;
    int brightness;
    int duration;
    int transition_count;
    VALUE vbitmap;
    VALUE vbitmap_t;
    int aimai;
} g_graphics;

struct FR_SuperSprite {
    void (*internal_draw)(VALUE,int,int);
    int y;
    int z;
};

struct FR_Viewport {
    void (*internal_draw)(VALUE,int,int);
    int y;
    int z;
    VALUE vdispose;
    VALUE vvisible;
    VALUE vrect;
    int ox;
    int oy;
    VALUE vcolor;
    VALUE vtone;
    int flash_count;
    int flash_count_start;
    unsigned char flash_red;
    unsigned char flash_green;
    unsigned char flash_blue;
    unsigned char flash_alpha;
    int flash_delete;

    //内部情報
    VALUE vsprites;
};

struct FR_Sprite {
    void (*internal_draw)(VALUE,int,int);
    int y;
    int z;
    VALUE vdispose;
    VALUE vvisible;
    VALUE vbitmap;
    VALUE vrect;
    VALUE vviewport;
    VALUE vcolor;
    VALUE vtone;
    int blend_type;
    int flash_count;
    int flash_delete;
    int x;
    int ox;
    int oy;
    float zoom_x;
    float zoom_y;
    float angle;
    int opacity;
    int flash_count_start;
    unsigned char flash_red;
    unsigned char flash_green;
    unsigned char flash_blue;
    unsigned char flash_alpha;
    int vmirror;
    int wave_amp;
    int wave_length;
    int wave_speed;
    int wave_phase;
    int bush_depth;
    int bush_opacity;
};

struct FR_Plane {
    void (*internal_draw)(VALUE,int,int);
    int y;
    int z;
    VALUE vdispose;
    VALUE vvisible;
    VALUE vbitmap;
    VALUE vviewport;
    VALUE vcolor;
    VALUE vtone;
    int blend_type;
    int ox;
    int oy;
    float zoom_x;
    float zoom_y;
    int opacity;
};

struct FR_Window {
    void (*internal_draw)(VALUE,int,int);
    int y;
    int z;
    VALUE vwindowskin;
    VALUE vcontents;
    VALUE vviewport;
    VALUE vcursor_rect;
    int x;
    VALUE vactive;
    VALUE vdispose;
    VALUE vvisible;
    VALUE vpause;
    int width;
    int height;
    int ox;
    int oy;
    int back_opacity;
    int contents_opacity;
    int opacity;
    int openness;
    int pause_count;
    int active_count;
    int active_flag;
};

struct FR_Tilemap {
    void (*internal_draw)(VALUE,int,int);
    int y;
    int z;
    VALUE vdispose;
    VALUE vvisible;
    VALUE vbitmaps;
    VALUE vviewport;
    VALUE vmap_data;
    VALUE vflash_data;
    VALUE vpassages;
    int ox;
    int oy;
    int count;
    VALUE sub;
};

struct FR_Tilemap_sub {
    void (*internal_draw)(VALUE,int,int);
    int y;
    int z;
    struct FR_Tilemap *parent;
};

struct FR_Bitmap {
    LPDIRECT3DTEXTURE9 pD3DTexture;     /* テクスチャ   */
    int width;
    int height;
    int real_width;
    int real_height;
    VALUE vfont;
};

struct FR_Rect {
    int x;
    int y;
    int width;
    int height;
};

struct Color {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char alpha;
};

struct FR_Color {
    double red;
    double green;
    double blue;
    double alpha;
    union{
        unsigned int c;
        struct Color color;
    };
};


struct FR_Tone {
    double red;
    double green;
    double blue;
    double gray;
};

struct FR_Font {
    VALUE vname;
    VALUE vsize;
    VALUE vbold;
    VALUE vitalic;
    VALUE vshadow;
    VALUE vcolor;
};
struct FR_Font g_default_font;

struct FR_Table {
    int count;
    int xsize;
    int ysize;
    int zsize;
    int total;
    short *memory;
};


/* Pad情報 */
static struct DXRubyPadInfo {
    int right;
    int left;
    int up;
    int down;
    LPDIRECTINPUTDEVICE8  pDIDJoyPad; /* DirectInputのパッドデバイス */
} g_PadInfo[PADMAX];

/* Pad状態 */
static struct DXRubyPadState {
    char button[20];
    int PadConfig[20];
    int count[20];
    int wait[20];
    int interval[20];
} g_PadState[PADMAX];

/* プロトタイプ宣言 */
static void InitWindow( void );
static void InitDXGraphics( void );
static void InitDirectInput( void );
LRESULT CALLBACK MainWndProc( HWND hWnd,UINT msg,UINT wParam,LONG lParam );
static void InitSync( void );
static __int64 GetSystemCounter( void );
static void Window_DirectXRelease( void );
static void Input_SetConfig( int number, int fr, int pad, int key );
static void ChangeSize( void );
static void inputupdate( void);
static VALUE Input_update( VALUE );
static VALUE Window_sync( VALUE );
static void Window_create( void );

static void release_Font( struct FR_Font* font );
static void release_Viewport( struct FR_Viewport* vp );
static void Viewport_internal_draw( VALUE self, int ox, int oy );
static void Sprite_internal_draw( VALUE self, int ox, int oy );
static void Plane_internal_draw( VALUE self, int ox, int oy );
static void Window_internal_draw( VALUE self, int ox, int oy );
static void Tilemap_internal_draw( VALUE self, int ox, int oy );
static void Tilemap_sub_internal_draw( VALUE self, int ox, int oy );
void SortSuperSpriteList( VALUE* vpsprites, int spritecount );
static VALUE Font_exist( VALUE klass, VALUE vstr );
static VALUE Bitmap_allocate( VALUE klass );
static VALUE Bitmap_initialize( int argc, VALUE *argv, VALUE self );
static VALUE Bitmap_text_size( VALUE self, VALUE vstr );
static VALUE Graphics_snap_to_bitmap( VALUE klass );
static VALUE Bitmap_dispose( VALUE self );
static VALUE Color_allocate( VALUE klass );
static VALUE Color_initialize( int argc, VALUE *argv, VALUE self );
static VALUE Bitmap_fill_rect( int argc, VALUE *argv, VALUE self );

/*********************************************************************
 * Windowモジュール
 * ウィンドウの管理・描画を行う。
 *********************************************************************/

/*--------------------------------------------------------------------
   ウィンドウの生成と初期化
 ---------------------------------------------------------------------*/
static void Window_create( void )
{
    HRESULT hr;
    RECT rect;

    /* ウィンドウ表示 */
    ShowWindow( g_hWnd, SW_HIDE );

    /* ウィンドウのサイズ設定 */
    rect.top     = 0;
    rect.left    = 0;
    rect.right   = g_WindowInfo.width * g_WindowInfo.scale;
    rect.bottom  = g_WindowInfo.height * g_WindowInfo.scale;

    /* ウィンドウのサイズ修正 */
    if( g_WindowInfo.windowed == Qnil || g_WindowInfo.windowed == Qfalse )
    {   /* フルスクリーン */
        SetWindowLong( g_hWnd, GWL_STYLE, WS_POPUP );
        SetWindowPos( g_hWnd, HWND_TOP, 0, 0, g_WindowInfo.width, g_WindowInfo.height, SWP_NOZORDER);
    }
    else
    {   /* ウィンドウモード */
        SetWindowLong( g_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
        AdjustWindowRect( &rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE );

        /* 幅と高さ計算 */
        rect.right   = rect.right - rect.left;
        rect.bottom  = rect.bottom - rect.top;

        /* ウィンドウ移動/サイズ設定 */
        if( g_WindowInfo.x == CW_USEDEFAULT )
        {   /* 位置がデフォルトの場合 */
            SetWindowPos( g_hWnd, HWND_TOP, 0, 0, rect.right, rect.bottom, SWP_NOZORDER | SWP_NOMOVE);
        }
        else
        {   /* 位置指定の場合 */
            SetWindowPos( g_hWnd, HWND_TOP, g_WindowInfo.x, g_WindowInfo.y, rect.right, rect.bottom, SWP_NOZORDER );
        }
    }

    /* DirectXのスクリーンサイズ変更 */
    ChangeSize();

    /* ウィンドウ表示 */
    ShowWindow( g_hWnd, SW_SHOWNORMAL );
    UpdateWindow( g_hWnd );

    /* シーンのクリア */
    g_pD3DDevice->lpVtbl->Clear( g_pD3DDevice, 0, NULL, D3DCLEAR_TARGET,
                                 D3DCOLOR_XRGB( g_WindowInfo.r, g_WindowInfo.g, g_WindowInfo.b ), 0, 0 );
    g_pD3DDevice->lpVtbl->Present( g_pD3DDevice, NULL, NULL, NULL, NULL );

    /* フレーム調整処理初期化 */
    InitSync();
}


/*--------------------------------------------------------------------
  （内部関数）スクリーンサイズ変更
 ---------------------------------------------------------------------*/
static void ChangeSize( void )
{
    D3DVIEWPORT9 vp;
    HRESULT hr;


    g_D3DPP.BackBufferWidth    = g_WindowInfo.width;
    g_D3DPP.BackBufferHeight   = g_WindowInfo.height;

    if( g_WindowInfo.windowed == Qnil || g_WindowInfo.windowed == Qfalse )
    {
        /* フルスクリーン時（32bitColor/60Hz固定) */
        g_D3DPP.BackBufferFormat           = D3DFMT_X8R8G8B8;
        g_D3DPP.Windowed                   = FALSE;
        g_D3DPP.FullScreen_RefreshRateInHz = 60;
        g_D3DPP.PresentationInterval       = D3DPRESENT_INTERVAL_ONE;
        g_WindowInfo.RefreshRate = 60;
    }
    else
    {
        /* ウィンドウモード時 */
        g_D3DPP.BackBufferFormat           = D3DFMT_UNKNOWN;
        g_D3DPP.Windowed                   = TRUE;
        g_D3DPP.FullScreen_RefreshRateInHz = 0;
        g_D3DPP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
        g_WindowInfo.RefreshRate = 0;
    }

    /* スプライトをロストさせる */
    if( g_pD3DXSprite )
    {
        g_pD3DXSprite->lpVtbl->OnLostDevice( g_pD3DXSprite );
    }

    /* 設定変更 */
    hr = g_pD3DDevice->lpVtbl->Reset( g_pD3DDevice, &g_D3DPP );
    if( FAILED( hr ) )
    {
        rb_raise( eFreeRGSSError, "設定に失敗しました - Reset" );
    }

    /* スプライト復帰 */
    if( g_pD3DXSprite )
    {
        g_pD3DXSprite->lpVtbl->OnResetDevice( g_pD3DXSprite );
    }

    /* ビューポートの設定 */
    vp.X       = 0;
    vp.Y       = 0;
    vp.Width   = g_D3DPP.BackBufferWidth;
    vp.Height  = g_D3DPP.BackBufferHeight;
    vp.MinZ    = 0.0f;
    vp.MaxZ    = 1.0f;

    hr = g_pD3DDevice->lpVtbl->SetViewport( g_pD3DDevice, &vp );

    if( FAILED( hr ) )
    {
        rb_raise( eFreeRGSSError, "設定に失敗しました - SetViewport" );
    }
}


/*--------------------------------------------------------------------
   （内部関数）ウィンドウプロシージャ
 ---------------------------------------------------------------------*/
LRESULT CALLBACK MainWndProc( HWND hWnd, UINT msg, UINT wParam, LONG lParam )
{
    RECT rect;
    
    switch( msg )
    {
    /* ウィンドウアクティブ／非アクティブ化 */
    case WM_ACTIVATE:
        g_bActive = (LOWORD(wParam) != 0);
        break;
    case WM_CLOSE:
        /* 自前ループの場合は無条件でキャセルする */
        if( g_WindowInfo.loop == 1 )
        {
            g_WindowInfo.requestclose = 1;
            return 0;
        }
        break;
    case WM_PAINT:
        g_pD3DDevice->lpVtbl->Present( g_pD3DDevice, NULL, NULL, NULL, NULL );
        break;
    /* ウィンドウ破棄 */
    case WM_DESTROY:
        /* ウインドウを閉じる */
        PostQuitMessage( 0 );
        g_hWnd = NULL;
        return 0;

    case WM_MOUSEWHEEL:
        g_WindowInfo.mousewheelpos += (short)HIWORD(wParam);
        break;
    }

    /* デフォルト処理 */
    return DefWindowProc( hWnd, msg, wParam, lParam );
}


/*--------------------------------------------------------------------
  （内部関数）フレーム調整
 ---------------------------------------------------------------------*/
static VALUE Window_sync( VALUE obj )
{
    __int64 NowTime;
    __int64 WaitTime;
    static __int64 BeforeSecond = 0;
    static int fps = 0;
    static int skip = 0;

    NowTime = GetSystemCounter();

    /* ウィンドウモード時 */
    if( g_WindowInfo.windowed != Qnil && g_WindowInfo.windowed != Qfalse )
    {
        g_OneFrameCount = NowTime - g_OldTime;
        if ( g_WindowInfo.fps > 0 ) /* fps指定がnil or 0の時はWait処理しない */
        {
            __int64 SleepTime;

            WaitTime = g_OneSecondCount / g_WindowInfo.fps;

            /* もう既に前回から１フレーム分の時間が経っていたら */
            if( g_OldTime + WaitTime < NowTime && skip == 0 )
            {
                /* コマ落ち制御しない場合 */
                if( g_WindowInfo.frameskip == Qfalse )
                {
                    fps++;
                    g_OldTime = NowTime;
                }
                else /* する場合 */
                {
                    /* 今回はウェイトも描画もしない */
                    skip++;
                    g_OldTime = g_OldTime + WaitTime;
                }
            }
            else
            {
                /* 前回描画を飛ばしたのに今回も間に合ってない場合 */
                if( g_OldTime + WaitTime < NowTime && skip == 1 )
                {
                    /* 諦めて処理落ち */
                    g_OldTime = NowTime;
                }
                else
                {
                    __int64 TempTime;
                    /* おおまかな時間をSleepで待つ */
                    TempTime = GetSystemCounter();
                    SleepTime = (WaitTime - (TempTime - g_OldTime)) * 1000 / g_OneSecondCount;
                    if( SleepTime > 2 )
                    {
                        Sleep( (unsigned long)(SleepTime - 2) );
                    }

                    TempTime = GetSystemCounter();

                    /* ループで厳密に処理をする */
                    for ( ; ; )
                    {
                        TempTime = GetSystemCounter();
                        if( g_OldTime +  WaitTime < TempTime )
                        {
                            break;
                        }
                    }
                    g_OldTime = g_OldTime +  WaitTime;
                }
                skip = 0;
                fps++;
            }
        }
        else
        {
            g_OldTime = NowTime;
            fps++;
        }

        /* FPS値設定 */
        if( (NowTime - BeforeSecond) >= g_OneSecondCount )
        {
            BeforeSecond = NowTime;
            g_WindowInfo.fpscheck = fps;
            fps = 0;
        }
    }
    else
    {
        g_OneFrameCount = NowTime - g_OldTime + g_DrawTime;
        WaitTime = g_OneSecondCount / g_WindowInfo.RefreshRate;

        /* もう既に前回から１フレーム分の時間が経っていたら */
        if( g_OldTime +  WaitTime - g_DrawTime < NowTime && skip == 0 )
        {
            /* 今回はウェイトも描画もしない */
            skip++;
//            g_OldTime = NowTime;
            return obj;
        }

        skip = 0;

//        g_OldTime = g_OldTime +  WaitTime;
        fps++;

        /* FPS値設定 */
        if( (NowTime - BeforeSecond) >= g_OneSecondCount )
        {
            BeforeSecond = NowTime;
            g_WindowInfo.fpscheck = fps;
            fps = 0;
        }
    }

    return obj;
}
/*--------------------------------------------------------------------
  （内部関数）フレーム調整用カウンタ値取得
 ---------------------------------------------------------------------*/
static __int64 GetSystemCounter( void )
{
    __int64 time;

    if( g_isPerformanceCounter == 1 )
    {
        QueryPerformanceCounter( (LARGE_INTEGER *)&time );
        return time;
    }
    else
    {
        return timeGetTime();
    }
}


/*--------------------------------------------------------------------
   ウィンドウのモード（ウィンドウ/全画面）を設定する。
 ---------------------------------------------------------------------*/
static VALUE Window_setwindowed( VALUE obj, VALUE windowed )
{
    g_WindowInfo.windowed = windowed;

    if( g_WindowInfo.created == Qtrue )
    {
        g_WindowInfo.created = Qfalse;
        Window_create();
    }

    return g_WindowInfo.windowed;
}


/*--------------------------------------------------------------------
   終了時に実行する
 ---------------------------------------------------------------------*/
static VALUE Window_shutdown( VALUE obj )
{
    /* アイコンリソース解放 */
    if( g_WindowInfo.hIcon != 0 )
    {
        DestroyIcon(g_WindowInfo.hIcon);
    }

    /* マウス状態復元 */
    if( g_WindowInfo.enablemouse == Qfalse )
    {
        int c;
        c = ShowCursor( TRUE );
        while( c < 0 ) c = ShowCursor( TRUE );
    }

    /* DirectX解放 */
    Window_DirectXRelease();

    /* ウインドウ・クラスの登録解除 */
    UnregisterClass( "DXRuby", g_hInstance );

    /* フレーム調整の後始末 */
    timeEndPeriod( 1 );

	g_iRefAll--;
	if( g_iRefAll == 0 )
	{
		CoUninitialize();
	}

    return obj;
}


/*--------------------------------------------------------------------
   DirectXオブジェクトを解放する
 ---------------------------------------------------------------------*/
void Window_DirectXRelease()
{
    int i;
    HRESULT hr;

    /* スプライトオブジェクトの使用終了 */
    if( g_pD3DXSprite )
    {
        g_pD3DXSprite->lpVtbl->OnLostDevice( g_pD3DXSprite );
    }

    /* スプライトオブジェクト破棄 */
    RELEASE( g_pD3DXSprite );

    for( i = 0 ; i < g_JoystickCount; i++ )
    {
        /* DirectInputDevice(JoyPad)オブジェクトの使用終了 */
        if( g_pDIDJoyPad[i] )
        {
            g_pDIDJoyPad[i]->lpVtbl->Unacquire( g_pDIDJoyPad[i] ); 
        }

        /* DirectInputDevide(JoyPad)オブジェクトの破棄 */
        RELEASE( g_pDIDJoyPad[i] );
    }

    /* DirectInputDevice(Keyboard)オブジェクトの使用終了 */
    if( g_pDIDKeyBoard )
    {
           g_pDIDKeyBoard->lpVtbl->Unacquire( g_pDIDKeyBoard ); 
    }

    /* DirectInputDevide(Keyboard)オブジェクトの破棄 */
    RELEASE( g_pDIDKeyBoard );

    /* DirectInputオブジェクトの破棄 */
    RELEASE( g_pDInput );

    /* Direct3D Deviceオブジェクトの破棄 */
    RELEASE( g_pD3DDevice );

	/* Direct3Dオブジェクトの破棄 */
    RELEASE( g_pD3D );
}


/*********************************************************************
 * Graphicsモジュール
 *
 * 画面を制御するモジュール
 *********************************************************************/
/*--------------------------------------------------------------------
   Windowsメッセージ処理
 ---------------------------------------------------------------------*/
static VALUE Graphics_message( void )
{
    MSG msg;
    msg.message = WM_NULL;
    g_WindowInfo.loop = 1;

    /* メッセージループ */
    /* メッセージがなくなるまで処理をし続ける */
    /* メッセージが無い時はブロックをyieldする */
    while (1)
    {
        if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) != 0)
        {
            /* メッセージがある時 */
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            break;
        }
    }

    if( g_WindowInfo.requestclose == 1 )
    {
        g_WindowInfo.requestclose = 0;
        return Qtrue;
    }

    return Qfalse;
}

static VALUE Graphics_update( VALUE klass )
{
    HRESULT hr;
    static int max;
    __int64 drawStartCounter;

    /* fps調整 */
    Window_sync( klass );

    if( Graphics_message() == Qtrue )
    {
        rb_eval_string("exit");
    }

    g_graphics.frame_count++;

    while( 1 )
    {
        hr = g_pD3DDevice->lpVtbl->TestCooperativeLevel( g_pD3DDevice );
        if( FAILED( hr ) )
        {
            if( hr == D3DERR_DEVICELOST )  /* デバイスはロスト状態である */
            {
                Sleep( 100 );
                continue;
            }
            else if( hr == D3DERR_DEVICENOTRESET ) /* デバイスはロスト状態であるがリセット可能である */
            {
                /* ここへ来た時はデバイスがリセット可能状態である */
                /* スプライトをロストさせる */
                if( g_pD3DXSprite )
                {
                    g_pD3DXSprite->lpVtbl->OnLostDevice( g_pD3DXSprite );
                }

                hr = g_pD3DDevice->lpVtbl->Reset( g_pD3DDevice, &g_D3DPP ); /* 復元を試みる */
                if( FAILED( hr ) )
                {
                    if( hr == D3DERR_DEVICELOST )
                    {
                        return klass; /* またロストした */
                    }
                    rb_raise( eFreeRGSSError, "DirectX APIの呼び出しに失敗しました - Reset" );
                }

                if( g_pD3DXSprite ) /* スプライト復帰 */
                {
                    g_pD3DXSprite->lpVtbl->OnResetDevice( g_pD3DXSprite );
                }
                break;
            }
            else /* DirectXの内部エラー */
            {
                rb_raise( eFreeRGSSError, "DirectX APIの内部エラーが発生しました - TestCooperativeLevel" );
            }
        }
        else
        {
            break;
        }
    }

    drawStartCounter = GetSystemCounter();

    /* シーンのクリア */
    g_pD3DDevice->lpVtbl->Clear( g_pD3DDevice, 0, NULL, D3DCLEAR_TARGET,
                                 D3DCOLOR_XRGB( g_WindowInfo.r, g_WindowInfo.g, g_WindowInfo.b ), 0, 0 );

    /* シーンの描画開始 */
    if( SUCCEEDED( g_pD3DDevice->lpVtbl->BeginScene( g_pD3DDevice ) ) )
    {
        int i, j;
        int oldflag = 0;
        VALUE *vpsprites;
        int spritecount;

        /* スプライトの描画開始 */
        g_pD3DXSprite->lpVtbl->Begin( g_pD3DXSprite, D3DXSPRITE_ALPHABLEND );

        /* 拡大縮小フィルタ設定 */
        g_pD3DDevice->lpVtbl->SetSamplerState(g_pD3DDevice, 0, D3DSAMP_MINFILTER,
                                         D3DTEXF_POINT );
        g_pD3DDevice->lpVtbl->SetSamplerState(g_pD3DDevice, 0, D3DSAMP_MAGFILTER,
                                         D3DTEXF_POINT );
        /* デバイスに使用する頂点フォーマットをセット */
        g_pD3DDevice->lpVtbl->SetFVF(g_pD3DDevice, D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

        vpsprites = RARRAY_PTR( g_graphics.vsprites );
        spritecount = RARRAY_LEN( g_graphics.vsprites );

        /* スプライトのz順ソート */
        SortSuperSpriteList( vpsprites, spritecount );

        for( i = 0; i < spritecount; i++ )
        {
            FR_GET_STRUCT( SuperSprite, vpsprites[i] )->internal_draw( vpsprites[i], 0, 0 );
        }

        /* freeze中 */
        if( g_graphics.vbitmap != Qnil )
        {
            struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, g_graphics.vbitmap );
            float per = ((float)g_graphics.frame_count - g_graphics.transition_count) / g_graphics.duration;

            D3DLOCKED_RECT srctrect;
            D3DLOCKED_RECT dsttrect;
            struct Color *psrc;
            struct Color *pdst;

            if( g_graphics.vbitmap_t != Qnil )
            {
                struct FR_Bitmap *bitmap_t = FR_GET_STRUCT( Bitmap, g_graphics.vbitmap_t );
                bitmap->pD3DTexture->lpVtbl->LockRect( bitmap->pD3DTexture, 0, &dsttrect, 0, 0 );
                bitmap_t->pD3DTexture->lpVtbl->LockRect( bitmap_t->pD3DTexture, 0, &srctrect, 0, D3DLOCK_READONLY );

                for( i = 0; i < bitmap->height; i++ )
                {
                    pdst = (struct Color*)((char *)dsttrect.pBits + i * dsttrect.Pitch);
                    if( i >= bitmap_t->height )
                    {
                        psrc = (struct Color*)((char *)srctrect.pBits + (i % bitmap_t->height) * srctrect.Pitch);
                    }
                    else
                    {
                        psrc = (struct Color*)((char *)srctrect.pBits + i * srctrect.Pitch);
                    }

                    for( j = 0; j < bitmap->width; j++ )
                    {
                        struct Color src;
                        if( j >= bitmap_t->width )
                        {
                            src = *(psrc + (j % bitmap_t->width));
                        }
                        else
                        {
                            src = *(psrc);
                        }

                        if( src.red < per * 255 )
                        {
                            (*pdst).alpha = 0;
                        }
                        else if( src.red >= per * 255 + g_graphics.aimai )
                        {
                            (*pdst).alpha = 255;
                        }
                        else
                        {
                            (*pdst).alpha = 255 * (src.red - per * 255) / g_graphics.aimai;
//                            (*pdst).alpha = 128;
                        }

                        pdst++;
                        psrc++;
                    }
                }

                bitmap_t->pD3DTexture->lpVtbl->UnlockRect( bitmap_t->pD3DTexture, 0 );
                bitmap->pD3DTexture->lpVtbl->UnlockRect( bitmap->pD3DTexture, 0 );
            }

            {
                TLVERTX VertexDataTbl[6];

                /* 頂点１ */
                VertexDataTbl[0].x =  0;
                VertexDataTbl[0].y =  0;
                /* 頂点２ */
                VertexDataTbl[1].x = VertexDataTbl[3].x =  g_WindowInfo.width;
                VertexDataTbl[1].y = VertexDataTbl[3].y =  0;
                /* 頂点３ */
                VertexDataTbl[4].x = g_WindowInfo.width;
                VertexDataTbl[4].y = g_WindowInfo.height;
                /* 頂点４ */
                VertexDataTbl[2].x = VertexDataTbl[5].x = 0;
                VertexDataTbl[2].y = VertexDataTbl[5].y = g_WindowInfo.height;
                /* Ｚ座標 */
                VertexDataTbl[0].z      =  
                VertexDataTbl[1].z      =  
                VertexDataTbl[2].z      =  
                VertexDataTbl[3].z      =  
                VertexDataTbl[4].z      =  
                VertexDataTbl[5].z      =  0.0f;
                /* テクスチャ座標 */
                VertexDataTbl[0].tu     =  VertexDataTbl[5].tu = VertexDataTbl[2].tu = 0;
                VertexDataTbl[0].tv     =  VertexDataTbl[1].tv = VertexDataTbl[3].tv = 0;
                VertexDataTbl[1].tu     =  VertexDataTbl[3].tu = VertexDataTbl[4].tu = 1.0f;
                VertexDataTbl[4].tv     =  VertexDataTbl[5].tv = VertexDataTbl[2].tv = 1.0f;

                /* 頂点色 */
                VertexDataTbl[0].color  =  
                VertexDataTbl[1].color  =  
                VertexDataTbl[2].color  =  
                VertexDataTbl[3].color  =  
                VertexDataTbl[4].color  =  
                VertexDataTbl[5].color  =  D3DCOLOR_ARGB(255,255,255,255);
                /* 描画 */
                g_pD3DDevice->lpVtbl->SetTexture( g_pD3DDevice, 0, (IDirect3DBaseTexture9*)bitmap->pD3DTexture );
                g_pD3DDevice->lpVtbl->DrawPrimitiveUP( g_pD3DDevice, D3DPT_TRIANGLELIST, 2, VertexDataTbl, sizeof(TLVERTX) );
            }
        }
        else
        {
            /* brightness処理 */
            g_pD3DDevice->lpVtbl->SetRenderState(g_pD3DDevice, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            g_pD3DDevice->lpVtbl->SetRenderState(g_pD3DDevice, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

            if( g_graphics.brightness != 255 )
            {
                TLVERTX VertexDataTbl[6];

                /* 頂点１ */
                VertexDataTbl[0].x =  0;
                VertexDataTbl[0].y =  0;
                /* 頂点２ */
                VertexDataTbl[1].x = VertexDataTbl[3].x =  g_WindowInfo.width;
                VertexDataTbl[1].y = VertexDataTbl[3].y =  0;
                /* 頂点３ */
                VertexDataTbl[4].x = g_WindowInfo.width;
                VertexDataTbl[4].y = g_WindowInfo.height;
                /* 頂点４ */
                VertexDataTbl[2].x = VertexDataTbl[5].x = 0;
                VertexDataTbl[2].y = VertexDataTbl[5].y = g_WindowInfo.height;
                /* Ｚ座標 */
                VertexDataTbl[0].z      =  
                VertexDataTbl[1].z      =  
                VertexDataTbl[2].z      =  
                VertexDataTbl[3].z      =  
                VertexDataTbl[4].z      =  
                VertexDataTbl[5].z      =  0.0f;
                /* テクスチャ座標 */
                VertexDataTbl[0].tu     =  VertexDataTbl[5].tu = VertexDataTbl[2].tu = 0;
                VertexDataTbl[0].tv     =  VertexDataTbl[1].tv = VertexDataTbl[3].tv = 0;
                VertexDataTbl[1].tu     =  VertexDataTbl[3].tu = VertexDataTbl[4].tu = 0;
                VertexDataTbl[4].tv     =  VertexDataTbl[5].tv = VertexDataTbl[2].tv = 0;

                /* 頂点色 */
                VertexDataTbl[0].color  =  
                VertexDataTbl[1].color  =  
                VertexDataTbl[2].color  =  
                VertexDataTbl[3].color  =  
                VertexDataTbl[4].color  =  
                VertexDataTbl[5].color  =  D3DCOLOR_ARGB(255-g_graphics.brightness, 0,0,0);
                /* 描画 */
                g_pD3DDevice->lpVtbl->SetTexture(g_pD3DDevice, 0, NULL);
                g_pD3DDevice->lpVtbl->DrawPrimitiveUP( g_pD3DDevice, D3DPT_TRIANGLELIST, 2, VertexDataTbl, sizeof(TLVERTX) );
            }
        }

        /* スプライトの描画終了 */
        g_pD3DXSprite->lpVtbl->End( g_pD3DXSprite );
        /* シーンの描画終了 */
        g_pD3DDevice->lpVtbl->EndScene( g_pD3DDevice );
    }

    if( g_WindowInfo.windowed == Qnil || g_WindowInfo.windowed == Qfalse )
    {
        g_DrawTime = GetSystemCounter() - drawStartCounter;
    }

    /* シーンの表示 */
    hr = g_pD3DDevice->lpVtbl->Present( g_pD3DDevice, NULL, NULL, NULL, NULL );

    if( g_WindowInfo.windowed == Qnil || g_WindowInfo.windowed == Qfalse )
    {
        g_OldTime = GetSystemCounter();
    }

    return Qnil;
}

static VALUE Graphics_freeze( VALUE klass )
{
    g_graphics.vbitmap = Graphics_snap_to_bitmap( klass );
    return Qnil;
}

static VALUE Graphics_transition( int argc, VALUE* argv, VALUE klass )
{
    VALUE vbitmap;
    VALUE vtext;
    struct FR_Bitmap* bitmap_t;
    struct FR_Bitmap* bitmap_snap;
    VALUE vduration, vfilename, vaimai;
    int i;

    if( g_graphics.vbitmap == Qnil )
    {
        return Qnil;
    }

    rb_scan_args( argc, argv, "12", &vduration, &vfilename, &vaimai );

    vbitmap = Bitmap_allocate( cBitmap );

    if( vfilename == Qnil )
    {
        VALUE va[5];
        VALUE c[4];
        va[0] = INT2FIX( g_WindowInfo.width );
        va[1] = INT2FIX( g_WindowInfo.height );
        Bitmap_initialize( 2, va, vbitmap );
        va[0] = INT2FIX( 0 );
        va[1] = INT2FIX( 0 );
        va[2] = INT2FIX( g_WindowInfo.width );
        va[3] = INT2FIX( g_WindowInfo.height );
        va[4] = Color_allocate( cColor );
        c[0] = c[1] = c[2] = c[3] = INT2FIX( 255 );
        Color_initialize( 4, c, va[4] );
        Bitmap_fill_rect( 5, va, vbitmap );
    }
    else
    {
#ifdef HAVE_RB_ENC_STR_NEW
        vtext = rb_funcall( vfilename, rb_intern("encode"), 1, rb_str_new2("UTF-16LE") );
#else
        {
            char *buf;
            int bufsize;
            bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vfilename ), RSTRING_LEN( vfilename ), 0, 0);
            buf = alloca(bufsize * 2);
            MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vfilename ), RSTRING_LEN( vfilename ), (LPWSTR)buf, bufsize);
            vtext = rb_str_new( buf, bufsize*2 );
        }
#endif
        {
            WIN32_FIND_DATA fdata;
            HANDLE hFind;
            char *buf;
            int bufsize;
            LPSTR localestr;
            VALUE str;
            LPSTR widestr = alloca(RSTRING_LEN(vtext)+2);
            ZeroMemory( widestr, RSTRING_LEN(vtext)+2 );
            memcpy( widestr, RSTRING_PTR(vtext), RSTRING_LEN(vtext) );

            bufsize = WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)widestr, -1, 0, 0, 0, 0 );
            localestr = alloca( bufsize+2 );
            ZeroMemory( localestr, bufsize+1 );
            WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)widestr, -1, localestr, bufsize, 0, 0 );

            /* 拡張子省略 */
            for( i = strlen( localestr ) - 1; i >=0; i-- )
            {
                if( localestr[i] == '.' || localestr[i] == '\\' || localestr[i] == '/' )
                {
                    break;
                }
            }
            if( i == -1 || localestr[i] != '.' )
            {
                strcat( localestr, ".*" );
            }

            hFind = FindFirstFile( localestr, &fdata );
            if( hFind == INVALID_HANDLE_VALUE )
            {
                rb_raise( eFreeRGSSError, "No such file or directory - %s", localestr );
            }
            FindClose( hFind );

            for( i = strlen( localestr ) - 1; i >=0; i-- )
            {
                if( localestr[i] == '\\' || localestr[i] == '/' )
                {
                    break;
                }
            }
            if( i >= 0 )
            {
                localestr[i+1] = '\0';
            }
            else
            {
                localestr[0] = '\0';
            }
            buf = alloca( strlen( localestr ) + strlen( fdata.cFileName ) );
            strcpy( buf, localestr );
            strcat( buf, fdata.cFileName );

            str = rb_str_new2( buf );
            Bitmap_initialize( 1, &str, vbitmap );
        }
    }

    g_graphics.vbitmap_t = vbitmap;
    g_graphics.duration = NUM2INT( vduration );
    g_graphics.transition_count = g_graphics.frame_count;
    if( vfilename == Qnil )
    {
        g_graphics.aimai = 256;
    }
    else
    {
        g_graphics.aimai = vaimai == Qnil ? 40 : NUM2INT( vaimai );
    }

    for( i = 0; i < NUM2INT( vduration ); i++ )
    {
        Graphics_update( klass );
    }

    Bitmap_dispose( g_graphics.vbitmap );
    Bitmap_dispose( g_graphics.vbitmap_t );
    g_graphics.vbitmap = Qnil;
    g_graphics.vbitmap_t = Qnil;

    return Qnil;
}

static VALUE Graphics_wait( VALUE klass, VALUE vduration )
{
    int i;
    for( i = 0; i < NUM2INT( vduration ); i++ )
    {
        Graphics_update( klass );
    }
    return vduration;
}

static VALUE Graphics_fadeout( VALUE klass, VALUE vduration )
{
    int i;
    for( i = 0; i < NUM2INT( vduration ); i++ )
    {
        g_graphics.brightness = 255.0f - 255.0f * i / NUM2INT( vduration );
        Graphics_update( klass );
    }
    return vduration;
}

static VALUE Graphics_fadein( VALUE klass, VALUE vduration )
{
    int i;
    for( i = 0; i < NUM2INT( vduration ); i++ )
    {
        g_graphics.brightness = 255.0f * i / NUM2INT( vduration );
        Graphics_update( klass );
    }
    return vduration;
}

static VALUE Graphics_resize_screen( VALUE klass, VALUE vwidth, VALUE vheight )
{
    g_WindowInfo.width = NUM2INT( vwidth );
    g_WindowInfo.height = NUM2INT( vheight );
    Window_create();
    return Qnil;
}

/*--------------------------------------------------------------------
  ウィンドウタイトル設定
 ---------------------------------------------------------------------*/
static VALUE Graphics_set_title( VALUE obj, VALUE vtitle )
{
    VALUE vtext;
    Check_Type( vtitle, T_STRING );

#ifdef HAVE_RB_ENC_STR_NEW
    vtext = rb_funcall( vtitle, rb_intern("encode"), 1, rb_str_new2("UTF-16LE") );
#else
    {
        char *buf;
        int bufsize;
        bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vtitle ), RSTRING_LEN( vtitle ), 0, 0);
        buf = alloca(bufsize * 2);
        MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vtitle ), RSTRING_LEN( vtitle ), (LPWSTR)buf, bufsize);
        vtext = rb_str_new( buf, bufsize*2 );
    }
#endif
    {
        LPSTR widestr = alloca(RSTRING_LEN(vtext)+2);
        LPSTR localestr = alloca(RSTRING_LEN(vtext)+1);
        ZeroMemory( widestr, RSTRING_LEN(vtext)+2 );
        ZeroMemory( localestr, RSTRING_LEN(vtext)+1 );
        memcpy( widestr, RSTRING_PTR(vtext), RSTRING_LEN(vtext) );

        WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)widestr, -1, localestr, RSTRING_LEN(vtext)+1, 0, 0 );
        SetWindowText( g_hWnd, localestr );
    }
    return vtitle;
}


/*--------------------------------------------------------------------
   スクリーンショットをBitmapオブジェクトに作る
 ---------------------------------------------------------------------*/
static VALUE Graphics_snap_to_bitmap( VALUE klass )
{
    HRESULT hr;
    D3DDISPLAYMODE dmode;
    LPDIRECT3DSURFACE9 pBackSurface;
    LPDIRECT3DSURFACE9 pOffSurface;
    VALUE vbitmap;
    struct FR_Bitmap *bitmap;
    VALUE varg[2];
    D3DLOCKED_RECT srctrect;
    D3DLOCKED_RECT dsttrect;
    int i, j;
    RECT srcrect, dstrect;

    /* 現在のディスプレイのフォーマットなどを取得 */
    hr = g_pD3D->lpVtbl->GetAdapterDisplayMode(g_pD3D, D3DADAPTER_DEFAULT, &dmode);
    if( FAILED( hr ) )
    {
        rb_raise( eFreeRGSSError, "failed to snap - GetAdapterDisplayMode" );
    }

    vbitmap = Bitmap_allocate( cBitmap );
    varg[0] = INT2FIX( g_WindowInfo.width );
    varg[1] = INT2FIX( g_WindowInfo.height );
    vbitmap = Bitmap_initialize( 2, varg, vbitmap );
    bitmap = FR_GET_STRUCT( Bitmap, vbitmap );

    /* スナップ用サーフェイス作成 */
    hr = g_pD3DDevice->lpVtbl->CreateOffscreenPlainSurface(g_pD3DDevice,
            g_WindowInfo.width,
            g_WindowInfo.height,
            D3DFMT_X8R8G8B8,
            D3DPOOL_SYSTEMMEM, &pOffSurface, NULL);
    if( FAILED( hr ) )
    {
        rb_raise( eFreeRGSSError, "failed to snap - CreateOffscreenPlainSurface" );
    }

    /* スナップ */
//    hr = g_pD3DDevice->lpVtbl->GetFrontBufferData(g_pD3DDevice, 0, pSurface);
    hr = g_pD3DDevice->lpVtbl->GetBackBuffer(g_pD3DDevice, 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurface);
    if( FAILED( hr ) )
    {
        RELEASE(pBackSurface);
        RELEASE(pOffSurface);
        rb_raise( eFreeRGSSError, "failed to snap - GetBackBuffer" );
    }

    hr = g_pD3DDevice->lpVtbl->GetRenderTargetData( g_pD3DDevice, pBackSurface, pOffSurface );
    if( FAILED( hr ) )
    {
        RELEASE(pBackSurface);
        RELEASE(pOffSurface);
        rb_raise( eFreeRGSSError, "failed to snap - GetRenderTargetData" );
    }

    /* イメージコピー */
    dstrect.left = 0;
    dstrect.top = 0;
    dstrect.right = g_WindowInfo.width;
    dstrect.bottom = g_WindowInfo.height;

    hr = bitmap->pD3DTexture->lpVtbl->LockRect( bitmap->pD3DTexture, 0, &dsttrect, &dstrect, 0 );
    hr = pOffSurface->lpVtbl->LockRect( pOffSurface, &srctrect, &dstrect, D3DLOCK_READONLY );

    for( i = 0; i < g_WindowInfo.height; i++)
    {
        int *psrc = (int*)((char *)srctrect.pBits + i * srctrect.Pitch);
        int *pdst = (int*)((char *)dsttrect.pBits + i * dsttrect.Pitch);
        for( j = 0; j < g_WindowInfo.width; j++)
        {
                *(pdst++) = *(psrc++) | 0xff000000;
        }
    }

    bitmap->pD3DTexture->lpVtbl->UnlockRect( bitmap->pD3DTexture, 0 );
    pOffSurface->lpVtbl->UnlockRect( pOffSurface );

    RELEASE(pBackSurface);
    RELEASE(pOffSurface);

    return vbitmap;
}

static VALUE Graphics_frame_reset( VALUE klass )
{
    return klass;
}

static VALUE Graphics_get_width( VALUE klass )
{
    return INT2FIX( g_WindowInfo.width );
}

static VALUE Graphics_get_height( VALUE klass )
{
    return INT2FIX( g_WindowInfo.height );
}

static VALUE Graphics_set_frame_rate( VALUE klass, VALUE vfps )
{
    g_WindowInfo.fps = NUM2INT( vfps );
    return klass;
}

static VALUE Graphics_get_frame_rate( VALUE klass )
{
    return INT2FIX( g_WindowInfo.fps );
}

static VALUE Graphics_set_frame_count( VALUE klass, VALUE vframecount )
{
    g_graphics.frame_count = NUM2INT( vframecount );
    return klass;
}

static VALUE Graphics_get_frame_count( VALUE klass )
{
    return INT2FIX( g_graphics.frame_count );
}

static VALUE Graphics_set_brightness( VALUE klass, VALUE vbrightness )
{
    g_graphics.brightness = NUM2INT( vbrightness );
    return klass;
}

static VALUE Graphics_get_brightness( VALUE klass )
{
    return INT2FIX( g_graphics.brightness );
}



/*********************************************************************
 * Rectクラス
 *
 * 範囲情報を保持するクラス。
 *********************************************************************/

/*--------------------------------------------------------------------
   参照されなくなったときにGCから呼ばれる関数
 ---------------------------------------------------------------------*/
static void release_Rect( struct FR_Rect* rect )
{
    free( rect );
}

/*--------------------------------------------------------------------
   Rectクラスのallocate。メモリを確保する為にinitialize前に呼ばれる。
 ---------------------------------------------------------------------*/
static VALUE Rect_allocate( VALUE klass )
{
    VALUE obj;
    struct FR_Rect *rect;

    /* メモリ取得＆Rectオブジェクト生成 */
    rect = malloc(sizeof(struct FR_Rect));
    if( rect == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Rect_allocate" );
    obj = Data_Wrap_Struct(klass, 0, release_Rect, rect);

    rect->x = 0;
    rect->y = 0;
    rect->width = 0;
    rect->height = 0;

    return obj;
}

/*--------------------------------------------------------------------
   RectクラスのInitialize
 ---------------------------------------------------------------------*/
static VALUE Rect_initialize( VALUE self, VALUE vx, VALUE vy, VALUE vwidth, VALUE vheight )
{
    struct FR_Rect *rect = FR_GET_STRUCT( Rect, self );

    rect->x = NUM2INT( vx );
    rect->y = NUM2INT( vy );
    rect->width = NUM2INT( vwidth );
    rect->height = NUM2INT( vheight );

    return self;
}

static void Rect_copy( VALUE d, VALUE s)
{
    struct FR_Rect *rectd = FR_GET_STRUCT( Rect, d );
    struct FR_Rect *rects = FR_GET_STRUCT( Rect, s );

    rectd->x = rects->x;
    rectd->y = rects->y;
    rectd->width = rects->width;
    rectd->height = rects->height;
}

static VALUE Rect_load( VALUE klass, VALUE vstr )
{
    VALUE vrect;
    vrect = Rect_allocate( klass );
    memcpy( (int*)FR_GET_STRUCT( Rect, vrect ), (int*)RSTRING_PTR( vstr ), 16 );
    return vrect;
}

static VALUE Rect_dump( VALUE self, VALUE vlimit )
{
    return rb_str_new( (char*)FR_GET_STRUCT( Rect, self ), 16 );
}

static VALUE Rect_dup( VALUE self )
{
    struct FR_Rect *rect = FR_GET_STRUCT( Rect, self );
    struct FR_Rect *new_rect;
    VALUE obj;

    /* メモリ取得＆Rectオブジェクト生成 */
    new_rect = malloc(sizeof(struct FR_Rect));
    if( new_rect == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Rect_dup" );
    obj = Data_Wrap_Struct( cRect, 0, release_Rect, new_rect );

    Rect_copy( obj, self );

    return obj;
}

static VALUE Rect_equal( VALUE self, VALUE vrect )
{
    struct FR_Rect *rect1 = FR_GET_STRUCT( Rect, self );
    struct FR_Rect *rect2;
    FR_CHECK_TYPE( Rect, vrect );
    Data_Get_Struct( vrect, struct FR_Rect, rect2 );

    if( rect1->x == rect2->x && rect1->y == rect2->y &&
        rect1->width == rect2->width && rect1->height == rect2->height )
    {
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}

static VALUE Rect_set_x( VALUE self, VALUE vx )
{
    FR_GET_STRUCT( Rect, self )->x = NUM2INT( vx );
    return vx;
}
static VALUE Rect_get_x( VALUE self )
{
    return INT2FIX( FR_GET_STRUCT( Rect, self )->x );
}
static VALUE Rect_set_y( VALUE self, VALUE vy )
{
    FR_GET_STRUCT( Rect, self )->y = NUM2INT( vy );
    return vy;
}
static VALUE Rect_get_y( VALUE self )
{
    return INT2FIX( FR_GET_STRUCT( Rect, self )->y );
}
static VALUE Rect_set_width( VALUE self, VALUE vwidth )
{
    FR_GET_STRUCT( Rect, self )->width = NUM2INT( vwidth );
    return vwidth;
}
static VALUE Rect_get_width( VALUE self )
{
    return INT2FIX( FR_GET_STRUCT( Rect, self )->width );
}
static VALUE Rect_set_height( VALUE self, VALUE vheight )
{
    FR_GET_STRUCT( Rect, self )->height = NUM2INT( vheight );
    return vheight;
}
static VALUE Rect_get_height( VALUE self )
{
    return INT2FIX( FR_GET_STRUCT( Rect, self )->height );
}
static VALUE Rect_to_s( VALUE self )
{
    struct FR_Rect *rect = FR_GET_STRUCT( Rect, self );
    char buf[128];
    sprintf( buf, "(%d, %d, %d, %d)", rect->x, rect->y, rect->width, rect->height );
    return rb_locale_str_new( buf, strlen( buf ) );
}
static VALUE Rect_empty( VALUE self )
{
    struct FR_Rect *rect = FR_GET_STRUCT( Rect, self );
    rect->x = 0;
    rect->y = 0;
    rect->width = 0;
    rect->height = 0;
    return self;
}


/*********************************************************************
 * Colorクラス
 *
 * 色情報を保持するクラス。
 *********************************************************************/

/*--------------------------------------------------------------------
   参照されなくなったときにGCから呼ばれる関数
 ---------------------------------------------------------------------*/
static void release_Color( struct FR_Color* color )
{
    free( color );
}

/*--------------------------------------------------------------------
   Colorクラスのallocate。メモリを確保する為にinitialize前に呼ばれる。
 ---------------------------------------------------------------------*/
static VALUE Color_allocate( VALUE klass )
{
    VALUE obj;
    struct FR_Color *color;

    /* メモリ取得＆Colorオブジェクト生成 */
    color = malloc(sizeof(struct FR_Color));
    if( color == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Color_allocate" );
    obj = Data_Wrap_Struct(klass, 0, release_Color, color);

    color->red = 0;
    color->green = 0;
    color->blue = 0;
    color->alpha = 0;
    color->c = 0;

    return obj;
}

static void Color_set_int( struct FR_Color *color)
{
    color->color.red = (unsigned char)color->red;
    color->color.green = (unsigned char)color->green;
    color->color.blue = (unsigned char)color->blue;
    color->color.alpha = (unsigned char)color->alpha;
}

/*--------------------------------------------------------------------
   ColorクラスのInitialize
 ---------------------------------------------------------------------*/
static VALUE Color_initialize( int argc, VALUE *argv, VALUE self )
{
    struct FR_Color *color = FR_GET_STRUCT( Color, self );
    VALUE vred, vgreen, vblue, valpha;

    rb_scan_args( argc, argv, "31", &vred, &vgreen, &vblue, &valpha );

    color->red = FR_0_255( (NUM2DBL( vred ) ) );
    color->green = FR_0_255( NUM2DBL( vgreen ) );
    color->blue = FR_0_255( NUM2DBL( vblue ) );
    color->alpha = valpha == Qnil ? 255 : FR_0_255( NUM2DBL( valpha ) );
    Color_set_int( color );

    return self;
}

static void Color_copy( VALUE d, VALUE s)
{
    struct FR_Color *colord = FR_GET_STRUCT( Color, d );
    struct FR_Color *colors = FR_GET_STRUCT( Color, s );

    colord->red = colors->red;
    colord->green = colors->green;
    colord->blue = colors->blue;
    colord->alpha = colors->alpha;
    colord->c = colors->c;
}

static VALUE Color_load( VALUE klass, VALUE vstr )
{
    VALUE vcolor;
    vcolor = Color_allocate( klass );
    memcpy( (double*)FR_GET_STRUCT( Color, vcolor ), (double*)RSTRING_PTR( vstr ), 32 );
    Color_set_int( FR_GET_STRUCT( Color, vcolor ) );
    return vcolor;
}

static VALUE Color_dump( VALUE self, VALUE vlimit )
{
    return rb_str_new( (char*)FR_GET_STRUCT( Color, self ), 32 );
}

static VALUE Color_dup( VALUE self )
{
    struct FR_Color *color = FR_GET_STRUCT( Color, self );
    struct FR_Color *new_color;
    VALUE obj;

    /* メモリ取得＆Colorオブジェクト生成 */
    new_color = malloc(sizeof(struct FR_Color));
    if( new_color == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Color_dup" );
    obj = Data_Wrap_Struct( cColor, 0, release_Color, new_color );

    Color_copy( obj, self );

    return obj;
}

static VALUE Color_equal( VALUE self, VALUE vcolor )
{
    struct FR_Color *color1 = FR_GET_STRUCT( Color, self );
    struct FR_Color *color2;
    FR_CHECK_TYPE( Color, vcolor );
    Data_Get_Struct( vcolor, struct FR_Color, color2 );

    if( color1->alpha == color2->alpha && color1->red == color2->red &&
        color1->green == color2->green && color1->blue == color2->blue )
    {
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}

static VALUE Color_set_red( VALUE self, VALUE vred )
{
    FR_GET_STRUCT( Color, self )->red = FR_0_255( NUM2DBL( vred ) );
    Color_set_int( FR_GET_STRUCT( Color, self ) );
    return vred;
}
static VALUE Color_get_red( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Color, self )->red );
}
static VALUE Color_set_green( VALUE self, VALUE vgreen )
{
    FR_GET_STRUCT( Color, self )->green = FR_0_255( NUM2DBL( vgreen ) );
    Color_set_int( FR_GET_STRUCT( Color, self ) );
    return vgreen;
}
static VALUE Color_get_green( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Color, self )->green );
}
static VALUE Color_set_blue( VALUE self, VALUE vblue )
{
    FR_GET_STRUCT( Color, self )->blue = FR_0_255( NUM2DBL( vblue ) );
    Color_set_int( FR_GET_STRUCT( Color, self ) );
    return vblue;
}
static VALUE Color_get_blue( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Color, self )->blue );
}
static VALUE Color_set_alpha( VALUE self, VALUE valpha )
{
    FR_GET_STRUCT( Color, self )->alpha = FR_0_255( NUM2DBL( valpha ) );
    Color_set_int( FR_GET_STRUCT( Color, self ) );
    return valpha;
}
static VALUE Color_get_alpha( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Color, self )->alpha );
}
static VALUE Color_to_s( VALUE self )
{
    struct FR_Color *color = FR_GET_STRUCT( Color, self );
    char buf[128];
    sprintf( buf, "(%f, %f, %f, %f)", color->red, color->green, color->blue, color->alpha );
    return rb_locale_str_new( buf, strlen( buf ) );
}

/*********************************************************************
 * Toneクラス
 *
 * 色情報を保持するクラス。
 *********************************************************************/

/*--------------------------------------------------------------------
   参照されなくなったときにGCから呼ばれる関数
 ---------------------------------------------------------------------*/
static void release_Tone( struct FR_Tone* tone )
{
    free( tone );
}

/*--------------------------------------------------------------------
   Toneクラスのallocate。メモリを確保する為にinitialize前に呼ばれる。
 ---------------------------------------------------------------------*/
static VALUE Tone_allocate( VALUE klass )
{
    VALUE obj;
    struct FR_Tone *tone;

    /* メモリ取得＆Toneオブジェクト生成 */
    tone = malloc(sizeof(struct FR_Tone));
    if( tone == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Tone_allocate" );
    obj = Data_Wrap_Struct(klass, 0, release_Tone, tone);

    tone->red = 0;
    tone->green = 0;
    tone->blue = 0;
    tone->gray = 0;

    return obj;
}

/*--------------------------------------------------------------------
   ToneクラスのInitialize
 ---------------------------------------------------------------------*/
static VALUE Tone_initialize( int argc, VALUE *argv, VALUE self )
{
    struct FR_Tone *tone = FR_GET_STRUCT( Tone, self );
    VALUE vred, vgreen, vblue, vgray;

    rb_scan_args( argc, argv, "31", &vred, &vgreen, &vblue, &vgray );

    tone->red = FR_M255_255( NUM2DBL( vred ) );
    tone->green = FR_M255_255( NUM2DBL( vgreen ) );
    tone->blue = FR_M255_255( NUM2DBL( vblue ) );
    tone->gray = vgray == Qnil ? 0 : FR_M255_255( NUM2DBL( vgray ) );

    return self;
}

static void Tone_copy( VALUE d, VALUE s)
{
    struct FR_Tone *toned = FR_GET_STRUCT( Tone, d );
    struct FR_Tone *tones = FR_GET_STRUCT( Tone, s );

    toned->red = tones->red;
    toned->green = tones->green;
    toned->blue = tones->blue;
    toned->gray = tones->gray;
}

static VALUE Tone_load( VALUE klass, VALUE vstr )
{
    VALUE vtone;
    vtone = Tone_allocate( klass );
    memcpy( (double*)FR_GET_STRUCT( Tone, vtone ), (double*)RSTRING_PTR( vstr ), 32 );
    return vtone;
}

static VALUE Tone_dump( VALUE self, VALUE vlimit )
{
    return rb_str_new( (char*)FR_GET_STRUCT( Tone, self ), 32 );
}

static VALUE Tone_dup( VALUE self )
{
    struct FR_Tone *tone = FR_GET_STRUCT( Tone, self );
    struct FR_Tone *new_tone;
    VALUE obj;

    /* メモリ取得＆Toneオブジェクト生成 */
    new_tone = malloc(sizeof(struct FR_Tone));
    if( new_tone == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Tone_dup" );
    obj = Data_Wrap_Struct( cTone, 0, release_Tone, new_tone );

    Tone_copy( obj, self );

    return obj;
}

static VALUE Tone_equal( VALUE self, VALUE vtone )
{
    struct FR_Tone *tone1 = FR_GET_STRUCT( Tone, self );
    struct FR_Tone *tone2;
    FR_CHECK_TYPE( Tone, vtone );
    Data_Get_Struct( vtone, struct FR_Tone, tone2 );

    if( tone1->gray == tone2->gray && tone1->red == tone2->red &&
        tone1->green == tone2->green && tone1->blue == tone2->blue )
    {
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}
static VALUE Tone_set_red( VALUE self, VALUE vred )
{
    FR_GET_STRUCT( Tone, self )->red = FR_M255_255( NUM2DBL( vred ) );
    return vred;
}
static VALUE Tone_get_red( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Tone, self )->red );
}
static VALUE Tone_set_green( VALUE self, VALUE vgreen )
{
    FR_GET_STRUCT( Tone, self )->green = FR_M255_255( NUM2DBL( vgreen ) );
    return vgreen;
}
static VALUE Tone_get_green( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Tone, self )->green );
}
static VALUE Tone_set_blue( VALUE self, VALUE vblue )
{
    FR_GET_STRUCT( Tone, self )->blue = FR_M255_255( NUM2DBL( vblue ) );
    return vblue;
}
static VALUE Tone_get_blue( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Tone, self )->blue );
}
static VALUE Tone_set_gray( VALUE self, VALUE vgray )
{
    FR_GET_STRUCT( Tone, self )->gray = FR_0_255( NUM2DBL( vgray ) );
    return vgray;
}
static VALUE Tone_get_gray( VALUE self )
{
    return rb_float_new( FR_GET_STRUCT( Tone, self )->gray );
}
static VALUE Tone_to_s( VALUE self )
{
    struct FR_Tone *tone = FR_GET_STRUCT( Tone, self );
    char buf[128];
    sprintf( buf, "(%f, %f, %f, %f)", tone->red, tone->green, tone->blue, tone->gray );
    return rb_locale_str_new( buf, strlen( buf ) );
}


/*********************************************************************
 * Fontクラス
 *
 * フォントの情報を保持する
 *********************************************************************/
/*--------------------------------------------------------------------
   参照されなくなったときにGCから呼ばれる関数
 ---------------------------------------------------------------------*/
static void release_Font( struct FR_Font *font )
{
    free( font );
}

/*--------------------------------------------------------------------
   Fontのmark関数
 ---------------------------------------------------------------------*/
static void mark_Font( struct FR_Font *font )
{
    rb_gc_mark( font->vname );
    rb_gc_mark( font->vsize );
    rb_gc_mark( font->vbold );
    rb_gc_mark( font->vitalic );
    rb_gc_mark( font->vshadow );
    rb_gc_mark( font->vcolor );
}

/*--------------------------------------------------------------------
   Fontクラスのallocate。メモリを確保する為にinitialize前に呼ばれる。
 ---------------------------------------------------------------------*/
static VALUE Font_allocate( VALUE klass )
{
    struct FR_Font *font;

    /* メモリ取得＆FR_Fontオブジェクト生成 */
    font = malloc( sizeof(struct FR_Font) );
    if( font == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Font_allocate" );

    font->vname = g_default_font.vname;
    font->vsize = g_default_font.vsize;
    font->vbold = g_default_font.vbold;
    font->vitalic = g_default_font.vitalic;
    font->vshadow = g_default_font.vshadow;
    font->vcolor = g_default_font.vcolor;

    return Data_Wrap_Struct( klass, mark_Font, release_Font, font );
}


/*--------------------------------------------------------------------
   FontクラスのInitialize
 ---------------------------------------------------------------------*/
static VALUE Font_initialize( int argc, VALUE *argv, VALUE self )
{
    struct FR_Font *font = FR_GET_STRUCT( Font, self );
    VALUE vname, vsize;

    rb_scan_args( argc, argv, "02", &vname, &vsize );

    if( vname != Qnil )
    {
        font->vname = vname;
    }
    else
    {
        font->vname = g_default_font.vname;
        if( vsize != Qnil )
        {
            font->vsize = FIX2INT( vsize );
        }
        else
        {
            font->vsize = g_default_font.vsize;
        }
    }

    return self;
}

// フォント列挙コールバック関数
int CALLBACK EnumFontFamExProc( ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntm,
                                                  int FontType, LPARAM lParam )
{
    if( strcmp( lpelfe->elfLogFont.lfFaceName, (char*)lParam ) == 0 ) return 0;
    return 1;
}

static VALUE Font_exist( VALUE klass, VALUE vstr )
{
    HDC hdc;
    LOGFONTW LogFont;
    int result;
    VALUE vwidestr;
    LPSTR widestr;

    Check_Type( vstr, T_STRING );
    hdc = GetDC( g_hWnd );

    ZeroMemory( &LogFont, sizeof(LOGFONTW) );
    LogFont.lfCharSet = DEFAULT_CHARSET;

    /* フォント名のUTF16化 */
#ifdef HAVE_RB_ENC_STR_NEW
    vwidestr = rb_funcall( vstr, rb_intern( "encode" ), 1, rb_str_new2( "UTF-16LE" ) );
#else
    {
        char *buf;
        int bufsize;
        bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vstr ), RSTRING_LEN( vstr ), 0, 0);
        buf = alloca(bufsize * 2);
        MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vstr ), RSTRING_LEN( vstr ), (LPWSTR)buf, bufsize);
        vwidestr = rb_str_new( buf, bufsize*2 );
    }
#endif
    widestr = alloca( RSTRING_LEN( vwidestr ) + 2 );
    ZeroMemory( widestr, RSTRING_LEN( vwidestr ) + 2 );
    memcpy( widestr, RSTRING_PTR( vwidestr ), RSTRING_LEN( vwidestr ) );

    result = EnumFontFamiliesExW( hdc, &LogFont, (FONTENUMPROCW)EnumFontFamExProc, (LPARAM)RSTRING_PTR( vwidestr ), 0 );
    ReleaseDC( g_hWnd, hdc );

    return result == 0 ? Qtrue : Qfalse;
}


/*--------------------------------------------------------------------
   Fontクラスのinstall
 ---------------------------------------------------------------------*/
static VALUE Font_install( VALUE klass, VALUE vstr )
{
    int result;
    Check_Type( vstr, T_STRING );

    result = AddFontResourceEx( RSTRING_PTR( vstr ), 0x10, 0 );
    if( result == 0 )
    {
        rb_raise( eFreeRGSSError, "failed to font install - Font_install" );
    }

    return INT2FIX( result );
}

static VALUE Font_set_name( VALUE self, VALUE vname )
{
    FR_GET_STRUCT( Font, self )->vname = vname;
    return vname;
}
static VALUE Font_get_name( VALUE self )
{
    return FR_GET_STRUCT( Font, self )->vname;
}
static VALUE Font_set_default_name( VALUE klass, VALUE vname )
{
    g_default_font.vname = vname;
    return vname;
}
static VALUE Font_get_default_name( VALUE klass )
{
    return g_default_font.vname;
}
static VALUE Font_set_size( VALUE self, VALUE vsize )
{
    if( NUM2INT( vsize ) < 6 || NUM2INT( vsize ) > 96 ) rb_raise( eFreeRGSSError, "bad value of size");
    FR_GET_STRUCT( Font, self )->vsize = vsize;
    return vsize;
}
static VALUE Font_get_size( VALUE self )
{
    return FR_GET_STRUCT( Font, self )->vsize;
}
static VALUE Font_set_default_size( VALUE klass, VALUE vsize )
{
    if( NUM2INT( vsize ) < 6 || NUM2INT( vsize ) > 96 ) rb_raise( eFreeRGSSError, "bad value of size");
    g_default_font.vsize = vsize;
    return vsize;
}
static VALUE Font_get_default_size( VALUE klass )
{
    return g_default_font.vsize;
}
static VALUE Font_set_bold( VALUE self, VALUE vbold )
{
    FR_GET_STRUCT( Font, self )->vbold = FR_IS_TRUE( vbold );
    return vbold;
}
static VALUE Font_get_bold( VALUE self )
{
    return FR_GET_STRUCT( Font, self )->vbold;
}
static VALUE Font_set_default_bold( VALUE klass, VALUE vbold )
{
    g_default_font.vbold = FR_IS_TRUE( vbold );
    return vbold;
}
static VALUE Font_get_default_bold( VALUE klass )
{
    return g_default_font.vbold;
}
static VALUE Font_set_italic( VALUE self, VALUE vitalic )
{
    FR_GET_STRUCT( Font, self )->vitalic = FR_IS_TRUE( vitalic );
    return vitalic;
}
static VALUE Font_get_italic( VALUE self )
{
    return FR_GET_STRUCT( Font, self )->vitalic;
}
static VALUE Font_set_default_italic( VALUE klass, VALUE vitalic )
{
    g_default_font.vitalic = FR_IS_TRUE( vitalic );
    return vitalic;
}
static VALUE Font_get_default_italic( VALUE klass )
{
    return g_default_font.vitalic;
}
static VALUE Font_set_shadow( VALUE self, VALUE vshadow )
{
    FR_GET_STRUCT( Font, self )->vshadow = FR_IS_TRUE( vshadow );
    return vshadow;
}
static VALUE Font_get_shadow( VALUE self )
{
    return FR_GET_STRUCT( Font, self )->vshadow;
}
static VALUE Font_set_default_shadow( VALUE klass, VALUE vshadow )
{
    g_default_font.vshadow = FR_IS_TRUE( vshadow );
    return vshadow;
}
static VALUE Font_get_default_shadow( VALUE klass )
{
    return g_default_font.vshadow;
}
static VALUE Font_set_color( VALUE self, VALUE vcolor )
{
    FR_CHECK_TYPE( Color, vcolor );
    FR_GET_STRUCT( Font, self )->vcolor = vcolor;
    return vcolor;
}
static VALUE Font_get_color( VALUE self )
{
    return FR_GET_STRUCT( Font, self )->vcolor;
}
static VALUE Font_set_default_color( VALUE klass, VALUE vcolor )
{
    FR_CHECK_TYPE( Color, vcolor );
    g_default_font.vcolor = vcolor;
    return vcolor;
}
static VALUE Font_get_default_color( VALUE klass )
{
    return g_default_font.vcolor;
}


/*********************************************************************
 * Bitmapクラス
 *
 * 描画用の画像を保持するクラス。
 *********************************************************************/

/*--------------------------------------------------------------------
   参照されなくなったときにGCから呼ばれる関数
 ---------------------------------------------------------------------*/
static void release_Bitmap( struct FR_Bitmap* bitmap )
{
    if( bitmap->pD3DTexture )
    {
        RELEASE( bitmap->pD3DTexture );
        g_iRefAll--;
        if( g_iRefAll == 0 )
        {
            CoUninitialize();
        }
    }
    free( bitmap );
}

/*--------------------------------------------------------------------
   Bitmapのmark関数
 ---------------------------------------------------------------------*/
static void mark_Bitmap( struct FR_Bitmap *bitmap )
{
    rb_gc_mark( bitmap->vfont );
}

/*--------------------------------------------------------------------
   Bitmapクラスのallocate。メモリを確保する為にinitialize前に呼ばれる。
 ---------------------------------------------------------------------*/
static VALUE Bitmap_allocate( VALUE klass )
{
    struct FR_Bitmap *bitmap;
    VALUE obj;

    /* メモリ取得＆Bitmapオブジェクト生成 */
    bitmap = malloc(sizeof(struct FR_Bitmap));
    if( bitmap == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Bitmap_allocate" );

    bitmap->vfont = Qnil;
    obj = Data_Wrap_Struct(klass, mark_Bitmap, release_Bitmap, bitmap);

    bitmap->pD3DTexture = NULL;
    bitmap->width = 0;
    bitmap->height = 0;
    bitmap->real_width = 0;
    bitmap->real_height = 0;
    bitmap->vfont = Font_allocate( cFont );
    return obj;
}

/*--------------------------------------------------------------------
    Bitmapのデータ設定(内部処理用box描画)
 ---------------------------------------------------------------------*/
static void Bitmap_fill( int x1, int y1, int width, int height, unsigned int col, struct FR_Bitmap *bitmap )
{
    D3DLOCKED_RECT texrect;
    int x, y;
    RECT rect;
    unsigned int *p;

    if( x1 < 0 )
    {
        x1 = 0;
    }
    if( y1 < 0 )
    {
        y1 = 0;
    }
    if( x1 + width > bitmap->width )
    {
        width = bitmap->width - x1;
    }
    if( y1 + height > bitmap->height )
    {
        height = bitmap->height - y1;
    }

    rect.left = x1;
    rect.top = y1;
    rect.right = x1 + width;
    rect.bottom = y1 + height;
    bitmap->pD3DTexture->lpVtbl->LockRect( bitmap->pD3DTexture, 0, &texrect, &rect, 0 );
    for( y = 0; y < height; y++ )
    {
        p = (unsigned int*)((char *)texrect.pBits + y * texrect.Pitch);
        for( x = 0; x < width; x++ )
        {
            *(p++) = col;
        }
    }
    bitmap->pD3DTexture->lpVtbl->UnlockRect( bitmap->pD3DTexture, 0 );
    return;
}

/*--------------------------------------------------------------------
   BitmapクラスのInitialize
 ---------------------------------------------------------------------*/
static VALUE Bitmap_initialize( int argc, VALUE *argv, VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    HRESULT hr;
    D3DSURFACE_DESC desc;
    D3DXIMAGE_INFO srcinfo;
    VALUE arg1, arg2;
    int width, height, i;

    rb_scan_args( argc, argv, "11", &arg1, &arg2 );

    if( TYPE( arg1 ) == T_STRING )
    {
        VALUE vtext;
#ifdef HAVE_RB_ENC_STR_NEW
        vtext = rb_funcall( arg1, rb_intern("encode"), 1, rb_str_new2("UTF-16LE") );
#else
        {
            char *buf;
            int bufsize;
            bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( arg1 ), RSTRING_LEN( arg1 ), 0, 0);
            buf = alloca(bufsize * 2);
            MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( arg1 ), RSTRING_LEN( arg1 ), (LPWSTR)buf, bufsize);
            vtext = rb_str_new( buf, bufsize*2 );
        }
#endif
        {
            WIN32_FIND_DATA fdata;
            HANDLE hFind;
            char* buf;
            int bufsize;
            LPSTR localestr;
            LPSTR widestr = alloca(RSTRING_LEN(vtext)+2);
            ZeroMemory( widestr, RSTRING_LEN(vtext)+2 );
            memcpy( widestr, RSTRING_PTR(vtext), RSTRING_LEN(vtext) );

            bufsize = WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)widestr, -1, 0, 0, 0, 0 );
            localestr = alloca( bufsize+10 );
            ZeroMemory( localestr, bufsize+1 );
            WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)widestr, -1, localestr, bufsize, 0, 0 );

            /* 拡張子省略 */
            for( i = strlen( localestr ) - 1; i >=0; i-- )
            {
                if( localestr[i] == '.' || localestr[i] == '\\' || localestr[i] == '/' )
                {
                    break;
                }
            }
            if( i == -1 || localestr[i] != '.' )
            {
                strcat( localestr, ".*" );
            }

            hFind = FindFirstFile( localestr, &fdata );
            if( hFind == INVALID_HANDLE_VALUE )
            {
                rb_raise( eFreeRGSSError, "No such file or directory - %s", localestr );
            }
            FindClose( hFind );

            for( i = strlen( localestr ) - 1; i >=0; i-- )
            {
                if( localestr[i] == '\\' || localestr[i] == '/' )
                {
                    break;
                }
            }
            if( i >= 0 )
            {
                localestr[i+1] = '\0';
            }
            else
            {
                localestr[0] = '\0';
            }

            buf = alloca( strlen( localestr ) + strlen( fdata.cFileName ) );
            strcpy( buf, localestr );
            strcat( buf, fdata.cFileName );

            /* ファイル情報取得 */
            hr = D3DXGetImageInfoFromFile( buf, &srcinfo );

            if( FAILED( hr ) )
            {
                rb_raise( eFreeRGSSError, "No such file or directory1 - %s", buf );
            }

            /* ファイルを読み込んでテクスチャオブジェクトを作成する */
            hr = D3DXCreateTextureFromFileEx( g_pD3DDevice, buf, srcinfo.Width, srcinfo.Height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
                                              D3DX_DEFAULT,  D3DX_DEFAULT, 0,
                                              0, 0, &bitmap->pD3DTexture);

            if( FAILED( hr ) )
            {
                rb_raise( eFreeRGSSError, "No such file or directory2 - %s", fdata.cFileName );
            }
            width = srcinfo.Width;
            height = srcinfo.Height;
        }
    }
    else
    {
        width = NUM2INT( arg1 );
        height = NUM2INT( arg2 );

        if( width <= 0 || height <= 0 )
        {
            rb_raise( eFreeRGSSError, "failed to create bitmap - Bitmap_initialize" );
        }

        /* テクスチャオブジェクトを作成する */
        hr = D3DXCreateTexture( g_pD3DDevice, width, height,
                                1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
                                &bitmap->pD3DTexture);

        if( FAILED( hr ) )
        {
            rb_raise( eFreeRGSSError, "failed to create bitmap - Bitmap_initialize" );
        }
    }

    bitmap->pD3DTexture->lpVtbl->GetLevelDesc(bitmap->pD3DTexture, 0, &desc );
    bitmap->width = width;
    bitmap->height = height;
    bitmap->real_width = desc.Width;
    bitmap->real_height = desc.Height;

    g_iRefAll++;

    return self;
}


/*--------------------------------------------------------------------
   Bitmapクラスのfill_rect
 ---------------------------------------------------------------------*/
static VALUE Bitmap_fill_rect( int argc, VALUE *argv, VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    struct FR_Rect *rect;
    struct FR_Color *color;
    VALUE arg1, arg2, arg3, arg4, arg5, vcolor;
    int x, y, width, height, col;

    rb_scan_args( argc, argv, "23", &arg1, &arg2, &arg3, &arg4, &arg5 );

    FR_CHECK_BITMAP_DISPOSE( bitmap );

    if( TYPE( arg1 ) == T_FIXNUM )
    {
        x = NUM2INT( arg1 );
        y = NUM2INT( arg2 );
        width = NUM2INT( arg3 );
        height = NUM2INT( arg4 );
        vcolor = arg5;
    }
    else
    {
        FR_CHECK_TYPE( Rect, arg1 );
        Data_Get_Struct( arg1, struct FR_Rect, rect );
        x = rect->x;
        y = rect->y;
        width = rect->width;
        height = rect->height;
        vcolor = arg2;
    }
    FR_CHECK_TYPE( Color, vcolor );
    Data_Get_Struct( vcolor, struct FR_Color, color );

    Bitmap_fill( x, y, width, height, color->c, bitmap );

    return self;
}


/*--------------------------------------------------------------------
   Bitmapクラスのclear
 ---------------------------------------------------------------------*/
static VALUE Bitmap_clear( VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    FR_CHECK_BITMAP_DISPOSE( bitmap );
    Bitmap_fill( 0, 0, bitmap->width, bitmap->height, 0, bitmap );
    return self;
}


/*--------------------------------------------------------------------
   Bitmapクラスのclear_rect
 ---------------------------------------------------------------------*/
static VALUE Bitmap_clear_rect( int argc, VALUE *argv, VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    struct FR_Rect *rect;
    VALUE arg1, arg2, arg3, arg4;
    int x, y, width, height;

    rb_scan_args( argc, argv, "13", &arg1, &arg2, &arg3, &arg4 );

    FR_CHECK_BITMAP_DISPOSE( bitmap );

    if( TYPE( arg1 ) == T_FIXNUM )
    {
        x = NUM2INT( arg1 );
        y = NUM2INT( arg2 );
        width = NUM2INT( arg3 );
        height = NUM2INT( arg4 );
    }
    else
    {
        FR_CHECK_TYPE( Rect, arg1 );
        Data_Get_Struct( arg1, struct FR_Rect, rect );
        x = rect->x;
        y = rect->y;
        width = rect->width;
        height = rect->height;
    }

    Bitmap_fill( x, y, width, height, 0, bitmap );

    return self;
}


/*--------------------------------------------------------------------
   Bitmapクラスのset_pixel
 ---------------------------------------------------------------------*/
static VALUE Bitmap_set_pixel( VALUE self, VALUE vx, VALUE vy, VALUE vcolor )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    D3DLOCKED_RECT texrect;
    int x, y;
    RECT rect;

    FR_CHECK_BITMAP_DISPOSE( bitmap );

    x = NUM2INT( vx );
    y = NUM2INT( vy );
    FR_CHECK_TYPE( Color, vcolor);

    if( x < 0 || x >= bitmap->width || y < 0 || y >= bitmap->height )
    {
        return self;
    }

    rect.left = x;
    rect.top = y;
    rect.right = x + 1;
    rect.bottom = y + 1;
    bitmap->pD3DTexture->lpVtbl->LockRect( bitmap->pD3DTexture, 0, &texrect, &rect, 0 );

    *((unsigned int*)(texrect.pBits)) = ((struct FR_Color*)DATA_PTR( vcolor ))->c;

    bitmap->pD3DTexture->lpVtbl->UnlockRect( bitmap->pD3DTexture, 0 );

    return self;
}


/*--------------------------------------------------------------------
   Bitmapクラスのget_pixel
 ---------------------------------------------------------------------*/
static VALUE Bitmap_get_pixel( VALUE self, VALUE vx, VALUE vy )
{
    struct FR_Bitmap* bitmap = FR_GET_STRUCT( Bitmap, self );
    VALUE ary[4];
    VALUE vcolor;
    D3DLOCKED_RECT texrect;
    int x, y;
    RECT rect;

    FR_CHECK_BITMAP_DISPOSE( bitmap );

    x = NUM2INT( vx );
    y = NUM2INT( vy );

    vcolor = Color_allocate( cColor );
    
    if( x < 0 || x >= bitmap->width || y < 0 || y >= bitmap->height )
    {
        return vcolor;
    }

    rect.left = x;
    rect.top = y;
    rect.right = x + 1;
    rect.bottom = y + 1;
    bitmap->pD3DTexture->lpVtbl->LockRect( bitmap->pD3DTexture, 0, &texrect, &rect, D3DLOCK_READONLY );

    FR_GET_STRUCT( Color, vcolor )->red = (float)((struct Color*)texrect.pBits)->red;
    FR_GET_STRUCT( Color, vcolor )->green = (float)((struct Color*)texrect.pBits)->green;
    FR_GET_STRUCT( Color, vcolor )->blue = (float)((struct Color*)texrect.pBits)->blue;
    FR_GET_STRUCT( Color, vcolor )->alpha = (float)((struct Color*)texrect.pBits)->alpha;

    bitmap->pD3DTexture->lpVtbl->UnlockRect( bitmap->pD3DTexture, 0 );

    return vcolor;
}


static VALUE Bitmap_dispose( VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    FR_CHECK_BITMAP_DISPOSE( bitmap );
    RELEASE( bitmap->pD3DTexture );
    g_iRefAll--;
    if( g_iRefAll == 0 )
    {
        CoUninitialize();
    }
    return self;
}
static VALUE Bitmap_get_dispose( VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    FR_CHECK_BITMAP_DISPOSE( bitmap );
    return bitmap->pD3DTexture ? Qtrue : Qfalse;
}
static VALUE Bitmap_get_width( VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    FR_CHECK_BITMAP_DISPOSE( bitmap );
    return INT2FIX( bitmap->width );
}
static VALUE Bitmap_get_height( VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    FR_CHECK_BITMAP_DISPOSE( bitmap );
    return INT2FIX( bitmap->height );
}
static VALUE Bitmap_set_font( VALUE self, VALUE vfont )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    FR_CHECK_BITMAP_DISPOSE( bitmap );
    FR_CHECK_TYPE( Font, vfont );
    bitmap->vfont = vfont;
    return vfont;
}
static VALUE Bitmap_get_font( VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    FR_CHECK_BITMAP_DISPOSE( bitmap );
    return bitmap->vfont;
}
static VALUE Bitmap_get_rect( VALUE self )
{
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    struct FR_Rect *rect;
    VALUE vrect;

    FR_CHECK_BITMAP_DISPOSE( bitmap );

    /* メモリ取得＆Rectオブジェクト生成 */
    rect = malloc(sizeof(struct FR_Rect));
    if( rect == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Bitmap_get_rect" );
    vrect = Data_Wrap_Struct(cRect, 0, release_Rect, rect);

    rect->x = 0;
    rect->y = 0;
    rect->width = bitmap->width;
    rect->height = bitmap->height;

    return vrect;
}


/*--------------------------------------------------------------------
   BitmapにBitmap描画
 ---------------------------------------------------------------------*/
static VALUE Bitmap_blt( int argc, VALUE *argv, VALUE self )
{
    struct FR_Bitmap *bitmap_src;
    struct FR_Bitmap *bitmap_self = FR_GET_STRUCT( Bitmap, self );
    VALUE arg1,arg2,arg3,arg4,arg5;
    int opacity;

    int rx, ry, rwidth, rheight;
    int x, y;
    int i, j;
    D3DLOCKED_RECT srctrect;
    D3DLOCKED_RECT dsttrect;
    RECT srcrect;
    RECT dstrect;
    struct Color *psrc;
    struct Color *pdst;

    /* 引数取得 */
    rb_scan_args( argc, argv, "41", &arg1, &arg2, &arg3, &arg4, &arg5 );

    FR_CHECK_BITMAP_DISPOSE( bitmap_self );
    FR_CHECK_TYPE( Bitmap, arg3 );
    bitmap_src = FR_GET_STRUCT( Bitmap, arg3 );
    FR_CHECK_BITMAP_DISPOSE( bitmap_src );

    x = NUM2INT( arg1 );
    y = NUM2INT( arg2 );

    FR_CHECK_TYPE( Rect, arg4 );
    rx = FR_GET_STRUCT( Rect, arg4 )->x;
    ry = FR_GET_STRUCT( Rect, arg4 )->y;
    rwidth = FR_GET_STRUCT( Rect, arg4 )->width;
    rheight = FR_GET_STRUCT( Rect, arg4 )->height;

    opacity = arg5 == Qnil ? 255 : NUM2INT( arg5 );

    /* 画像のクリッピング */
    if( x < 0 )
    {
        rx -= x;
        rwidth -= x;
        x = 0;
    }
    if( y < 0 )
    {
        ry -= y;
        rheight -= y;
        y = 0;
    }
    if( rx < 0 )
    {
        x -= rx;
        rwidth -= x;
        rx = 0;
    }
    if( ry < 0 )
    {
        y -= ry;
        rheight -= ry;
        ry = 0;
    }
    if( x + rwidth > bitmap_self->width )
    {
        rwidth -= x + rwidth - bitmap_self->width;
    }
    if( y + rheight > bitmap_self->height )
    {
        rheight -= y + rheight - bitmap_self->height;
    }
    if( rx + rwidth > bitmap_src->width )
    {
        rwidth -= rx + rwidth - bitmap_src->width;
    }
    if( ry + rheight > bitmap_src->height )
    {
        rheight -= ry + rheight - bitmap_src->height;
    }

    /* 範囲外 */
    if( x >= bitmap_self->width || y >= bitmap_self->height || rx >= bitmap_src->width || ry >= bitmap_src->height ||
        rwidth < 0 || rheight < 0 )
    {
        return self;
    }

    if( bitmap_self == bitmap_src )
    {   /* 同じオブジェクトに対する描画なら全体ロック */
        bitmap_self->pD3DTexture->lpVtbl->LockRect( bitmap_self->pD3DTexture, 0, &dsttrect, 0, 0 );
        for( i = 0; i < rheight; i++ )
        {
            psrc = (struct Color*)((char *)dsttrect.pBits + rx * 4 + (ry + i) * dsttrect.Pitch);
            pdst = (struct Color*)((char *)dsttrect.pBits + x * 4 + (y + i) * dsttrect.Pitch);
            for( j = 0; j < rwidth; j++ )
            {
                struct Color src = *(psrc);
                src.alpha = src.alpha * opacity / 255;

                if( src.alpha == 255 )
                {
                    *pdst = src;
                }
                else if( src.alpha != 0 )
                {
                    struct Color d = *pdst;
                    struct Color data;

                    data.alpha = (255 - src.alpha) * d.alpha / 255 + src.alpha;
                    data.red = (src.alpha * src.red) / data.alpha + (int)d.alpha * d.red * (255 - src.alpha) / data.alpha / 255;
                    data.green = (src.alpha * src.green) / data.alpha + (int)d.alpha * d.green * (255 - src.alpha) / data.alpha / 255;
                    data.blue = (src.alpha * src.blue) / data.alpha + (int)d.alpha * d.blue * (255 - src.alpha) / data.alpha / 255;

                    *pdst = data;
                }
                pdst++;
                psrc++;
            }
        }
        bitmap_self->pD3DTexture->lpVtbl->UnlockRect( bitmap_self->pD3DTexture, 0 );
    }
    else
    {   /* 違うオブジェクトに対する描画なら部分ロック */
        dstrect.left = x;
        dstrect.top = y;
        dstrect.right = x + rwidth;
        dstrect.bottom = y + rheight;
        srcrect.left = rx;
        srcrect.top = ry;
        srcrect.right = rx + rwidth;
        srcrect.bottom = ry + rheight;

        bitmap_self->pD3DTexture->lpVtbl->LockRect( bitmap_self->pD3DTexture, 0, &dsttrect, &dstrect, 0 );
        bitmap_src->pD3DTexture->lpVtbl->LockRect( bitmap_src->pD3DTexture, 0, &srctrect, &srcrect, D3DLOCK_READONLY );

        for( i = 0; i < rheight; i++ )
        {
            psrc = (struct Color*)((char *)srctrect.pBits + i * srctrect.Pitch);
            pdst = (struct Color*)((char *)dsttrect.pBits + i * dsttrect.Pitch);
            for( j = 0; j < rwidth; j++ )
            {
                struct Color src = *(psrc);
                src.alpha = src.alpha * opacity / 255;

                if( src.alpha == 255 )
                {
                    *pdst = src;
                }
                else if( src.alpha != 0 )
                {
                    struct Color d = *pdst;
                    struct Color data;

                    data.alpha = (255 - src.alpha) * d.alpha / 255 + src.alpha;
                    data.red = (src.alpha * src.red) / data.alpha + (int)d.alpha * d.red * (255 - src.alpha) / data.alpha / 255;
                    data.green = (src.alpha * src.green) / data.alpha + (int)d.alpha * d.green * (255 - src.alpha) / data.alpha / 255;
                    data.blue = (src.alpha * src.blue) / data.alpha + (int)d.alpha * d.blue * (255 - src.alpha) / data.alpha / 255;

                    *pdst = data;
                }
                pdst++;
                psrc++;
            }
        }

        bitmap_self->pD3DTexture->lpVtbl->UnlockRect( bitmap_self->pD3DTexture, 0 );
        bitmap_src->pD3DTexture->lpVtbl->UnlockRect( bitmap_src->pD3DTexture, 0 );
    }

    return self;
}


/*--------------------------------------------------------------------
   Bitmapにフォント描画
 ---------------------------------------------------------------------*/
static VALUE Bitmap_draw_text( int argc, VALUE *argv, VALUE self )
{
    struct FR_Font *font;
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    VALUE arg1,arg2,arg3,arg4,arg5,arg6;
    int rx, ry, rwidth, rheight, align, tx, ty;
    int x, y, width, height;
    VALUE vstr;
    LPWSTR widestr;
    VALUE vwidestr;
    int cr, cg, cb, ca;
    HANDLE hFont;
    LOGFONTW logfont;
    int i, shadow;
    TEXTMETRIC tm;
    SIZE size;
    GLYPHMETRICS gm;
    MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};
    D3DLOCKED_RECT dsttrect;
    HDC hDC;
    int zoom;

    /* 引数取得 */
    rb_scan_args( argc, argv, "24", &arg1, &arg2, &arg3, &arg4, &arg5, &arg6 );

    FR_CHECK_BITMAP_DISPOSE( bitmap );
    FR_CHECK_TYPE( Font, bitmap->vfont );
    Data_Get_Struct( bitmap->vfont, struct FR_Font, font );

    if( TYPE( arg1 ) == T_FIXNUM )
    {
        rx = NUM2INT( arg1 );
        ry = NUM2INT( arg2 );
        rwidth = NUM2INT( arg3 );
        rheight = NUM2INT( arg4 );
        vstr = arg5;
        align = arg6 == Qnil ? 0 : NUM2INT( arg6 );
    }
    else
    {
        FR_CHECK_TYPE( Rect, arg1 );
        rx = ((struct FR_Rect*)DATA_PTR( arg1 ))->x;
        ry = ((struct FR_Rect*)DATA_PTR( arg1 ))->y;
        rwidth = ((struct FR_Rect*)DATA_PTR( arg1 ))->width;
        rheight = ((struct FR_Rect*)DATA_PTR( arg1 ))->height;
        vstr = arg2;
        align = arg3 == Qnil ? 0 : NUM2INT( arg3 );
    }
    Check_Type( vstr, T_STRING );

    if( rx >= bitmap->width || ry >= bitmap->height || rwidth <= 0 || rheight <= 0 || rx + rwidth < 0 || ry + rheight < 0 )
    {
        return self;
    }

    cr = ((struct FR_Color*)DATA_PTR( font->vcolor ))->red;
    cg = ((struct FR_Color*)DATA_PTR( font->vcolor ))->green;
    cb = ((struct FR_Color*)DATA_PTR( font->vcolor ))->blue;
    ca = ((struct FR_Color*)DATA_PTR( font->vcolor ))->alpha;

    /* フォント作成 */
    ZeroMemory( &logfont, sizeof(logfont) );
    logfont.lfHeight          = NUM2INT( font->vsize );
    logfont.lfWidth           = 0;
    logfont.lfWeight          = FR_IS_TRUE( font->vbold ) ? 1000 : 400;
    logfont.lfItalic          = FR_IS_TRUE( font->vitalic );
    logfont.lfCharSet         = DEFAULT_CHARSET;
    logfont.lfQuality         = ANTIALIASED_QUALITY;
    logfont.lfOutPrecision    = OUT_TT_ONLY_PRECIS;

    lstrcpyW(logfont.lfFaceName, (LPCWSTR)"\0");
    if( TYPE( font->vname ) == T_ARRAY )
    {
        /* 存在するフォントの検索 */
        for( i = 0; i < RARRAY_LEN( font->vname ); i++ )
        {
            if( Font_exist( cFont, RARRAY_PTR( font->vname )[i] ) == Qtrue )
            {
#ifdef HAVE_RB_ENC_STR_NEW
                vwidestr = rb_funcall( RARRAY_PTR( font->vname )[i], rb_intern( "encode" ), 1, rb_str_new2( "UTF-16LE" ) );
#else
                {
                    char *buf;
                    int bufsize;
                    bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( RARRAY_PTR( font->vname )[i] ), RSTRING_LEN( RARRAY_PTR( font->vname )[i] ), 0, 0);
                    buf = alloca(bufsize * 2);
                    MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( RARRAY_PTR( font->vname )[i] ), RSTRING_LEN( RARRAY_PTR( font->vname )[i] ), (LPWSTR)buf, bufsize);
                    vwidestr = rb_str_new( buf, bufsize*2 );
                }
#endif
                widestr = alloca( RSTRING_LEN( vwidestr ) + 2 );
                ZeroMemory( widestr, RSTRING_LEN( vwidestr ) + 2 );
                memcpy( widestr, RSTRING_PTR( vwidestr ), RSTRING_LEN( vwidestr ) );
                lstrcpyW( logfont.lfFaceName, widestr );
                break;
            }
        }
    }
    else if( TYPE( font->vname ) == T_STRING )
    {
#ifdef HAVE_RB_ENC_STR_NEW
        vwidestr = rb_funcall( font->vname, rb_intern( "encode" ), 1, rb_str_new2( "UTF-16LE" ) );
#else
        {
            char *buf;
            int bufsize;
            bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( font->vname ), RSTRING_LEN( font->vname ), 0, 0);
            buf = alloca(bufsize * 2);
            MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( font->vname ), RSTRING_LEN( font->vname ), (LPWSTR)buf, bufsize);
            vwidestr = rb_str_new( buf, bufsize*2 );
        }
#endif
        widestr = alloca( RSTRING_LEN( vwidestr ) + 2 );
        ZeroMemory( widestr, RSTRING_LEN( vwidestr ) + 2 );
        memcpy( widestr, RSTRING_PTR( vwidestr ), RSTRING_LEN( vwidestr ) );
        lstrcpyW( logfont.lfFaceName, widestr );
    }

    hFont = CreateFontIndirectW( &logfont );

    if( hFont == NULL )
    {
        rb_raise( eFreeRGSSError, "failed to create font - CreateFontIndirect" );
    }

    /* 描画文字のUTF16LE化 */
#ifdef HAVE_RB_ENC_STR_NEW
    vwidestr = rb_funcall( vstr, rb_intern( "encode" ), 1, rb_str_new2( "UTF-16LE" ) );
#else
    {
        char *buf;
        int bufsize;
        bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vstr ), RSTRING_LEN( vstr ), 0, 0);
        buf = alloca(bufsize * 2);
        MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vstr ), RSTRING_LEN( vstr ), (LPWSTR)buf, bufsize);
        vwidestr = rb_str_new( buf, bufsize*2 );
    }
#endif
    widestr = alloca( RSTRING_LEN( vwidestr ) + 2 );
    ZeroMemory( widestr, RSTRING_LEN( vwidestr ) + 2 );
    memcpy( widestr, RSTRING_PTR( vwidestr ), RSTRING_LEN( vwidestr ) );

    hDC = GetDC( g_hWnd );
    SelectObject( hDC, hFont );
    GetTextMetrics( hDC, &tm );

    /* 縦位置計算 */
    height = FIX2INT( font->vsize );
    y = ry - height / 2 + rheight / 2;
    if( y < ry )
    {
        y = ry;
    }
    if( height > rheight )
    {
        height = rheight;
    }

    /* 文字列の幅取得 */
    width = FR_GET_STRUCT( Rect, Bitmap_text_size( self, vwidestr ) )->width;

    switch( align )
    {
    case 1: /* 中央寄せ */
        x = rx - width / 2 + rwidth / 2;
        if( x < rx )
        {
            x = rx;
        }
        break;
    case 2: /* 右寄せ */
        x = rwidth - width;
        if( x < rx )
        {
            x = rx;
        }
        break;
    default: /* 左寄せ */
        x = rx;
        break;
    }
    /* 縮小率計算 */
    zoom = rwidth * 100 / width;
    if( zoom < 50 )
    {
        zoom = 50;
    }
    else
    if( zoom > 100 )
    {
        zoom = 100;
    }

    mat2.eM11.value = zoom / 100;
    mat2.eM11.fract = zoom * 65536 / 100;

    if( width > rwidth )
    {
        width = rwidth;
    }

    bitmap->pD3DTexture->lpVtbl->LockRect( bitmap->pD3DTexture, 0, &dsttrect, 0, 0 );

    if( FR_IS_TRUE(font->vshadow) )
    {
        tx = x + 1;
        ty = y + 1;
        for( i = 0; i < RSTRING_LEN( vwidestr ) / 2; i++ )
        {
            int bufsize = GetGlyphOutlineW( hDC, *(widestr + i), GGO_GRAY8_BITMAP,
                                            &gm, 0, NULL, &mat2 );
            unsigned char *buf = alloca( bufsize );
            int v, u;

            GetGlyphOutlineW( hDC, *(widestr + i), GGO_GRAY8_BITMAP, 
                              &gm, bufsize, (LPVOID)buf, &mat2 );

            for( v = 0; v < gm.gmBlackBoxY; v++ )
            {
                int yy = ty + tm.tmAscent - gm.gmptGlyphOrigin.y + v;
                if( yy < 0 )
                {
                    continue;
                }
                if( yy >= bitmap->height )
                {
                    break;
                }
                for( u = 0; u < gm.gmBlackBoxX; u++ )
                {
                    int xx, src;

                    xx = tx + gm.gmptGlyphOrigin.x + u;
                    if( xx < 0 )
                    {
                        continue;
                    }
                    if( xx >= bitmap->width || xx >= width )
                    {
                        break;
                    }

                    src = buf[ u + v * ((gm.gmBlackBoxX + 3) & 0xfffc) ] * 255 / 65;

                    if( src == 255 )
                    {
                        *((LPDWORD)((char*)dsttrect.pBits + xx * 4 + yy * dsttrect.Pitch)) = D3DCOLOR_ARGB(0xff, 0, 0, 0);
                    }
                    else if( src != 0 )
                    {
                        struct Color d = *((struct Color*)((char*)dsttrect.pBits + xx * 4 + yy * dsttrect.Pitch));
                        struct Color data;

                        data.alpha = (255 - src) * d.alpha / 255 + src;
                        data.red = (int)d.alpha * d.red * (255 - src) / data.alpha / 255;
                        data.green = (int)d.alpha * d.green * (255 - src) / data.alpha / 255;
                        data.blue = (int)d.alpha * d.blue * (255 - src) / data.alpha / 255;

                        *((struct Color*)((char*)dsttrect.pBits + xx * 4 + yy * dsttrect.Pitch)) = data;
                    }
                }
            }
            tx += gm.gmCellIncX;
            if( tx >= bitmap->width )
            {
                break;
            }
        }
    }

    for( i = 0; i < RSTRING_LEN( vwidestr ) / 2; i++ )
    {
        int bufsize = GetGlyphOutlineW( hDC, *(widestr + i), GGO_GRAY8_BITMAP,
                                        &gm, 0, NULL, &mat2 );
        unsigned char *buf = alloca( bufsize );
        int v, u;

        GetGlyphOutlineW( hDC, *(widestr + i), GGO_GRAY8_BITMAP, 
                          &gm, bufsize, (LPVOID)buf, &mat2 );

        for( v = 0; v < gm.gmBlackBoxY; v++ )
        {
            int yy = y + tm.tmAscent - gm.gmptGlyphOrigin.y + v;
            if( yy < 0 )
            {
                continue;
            }
            if( yy >= bitmap->height )
            {
                break;
            }
            for( u = 0; u < gm.gmBlackBoxX; u++ )
            {
                int xx, src;

                xx = x + gm.gmptGlyphOrigin.x + u;
                if( xx < 0 )
                {
                    continue;
                }
                if( xx >= bitmap->width || xx >= width )
                {
                    break;
                }

                src = (int)buf[ u + v * ((gm.gmBlackBoxX + 3) & 0xfffc) ] * 255 / 65;

                if( src == 255 )
                {
                    *((LPDWORD)((char*)dsttrect.pBits + xx * 4 + yy * dsttrect.Pitch)) = D3DCOLOR_ARGB(0xff, cr, cg, cb);
                }
                else if( src != 0 )
                {
                    struct Color d = *((struct Color*)((char*)dsttrect.pBits + xx * 4 + yy * dsttrect.Pitch));
                    struct Color data;

                    data.alpha = (255 - src) * d.alpha / 255 + src;
                    data.red = (src * cr) / data.alpha + (int)d.alpha * d.red * (255 - src) / data.alpha / 255;
                    data.green = (src * cg) / data.alpha + (int)d.alpha * d.green * (255 - src) / data.alpha / 255;
                    data.blue = (src * cb) / data.alpha + (int)d.alpha * d.blue * (255 - src) / data.alpha / 255;

                    *((struct Color*)((char*)dsttrect.pBits + xx * 4 + yy * dsttrect.Pitch)) = data;
                }
            }
        }
        x += gm.gmCellIncX;
        if( x >= bitmap->width )
        {
            break;
        }
    }

    bitmap->pD3DTexture->lpVtbl->UnlockRect( bitmap->pD3DTexture, 0 );

    DeleteObject( hFont );
    ReleaseDC( g_hWnd, hDC );
    return self;
}


/*--------------------------------------------------------------------
   幅を取得する
 ---------------------------------------------------------------------*/
static VALUE Bitmap_text_size( VALUE self, VALUE vstr )
{
    struct FR_Font *font;
    struct FR_Bitmap *bitmap = FR_GET_STRUCT( Bitmap, self );
    int tx;
    LPWSTR widestr;
    VALUE vwidestr;
    HANDLE hFont;
    LOGFONTW logfont;
    int i;
    GLYPHMETRICS gm;
    MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};
    HDC hDC;
    VALUE vrect;

    FR_CHECK_BITMAP_DISPOSE( bitmap );
    FR_CHECK_TYPE( Font, bitmap->vfont );
    Data_Get_Struct( bitmap->vfont, struct FR_Font, font );

    Check_Type( vstr, T_STRING );

    /* フォント作成 */
    ZeroMemory( &logfont, sizeof(logfont) );
    logfont.lfHeight          = NUM2INT( font->vsize );
    logfont.lfWidth           = 0;
    logfont.lfWeight          = font->vbold == Qnil || font->vbold == Qfalse ? 400 : 1000;
    logfont.lfItalic          = font->vitalic == Qnil || font->vitalic == Qfalse ? FALSE : TRUE;
    logfont.lfCharSet         = DEFAULT_CHARSET;
    logfont.lfQuality         = ANTIALIASED_QUALITY;
    logfont.lfOutPrecision    = OUT_TT_ONLY_PRECIS;

    lstrcpyW(logfont.lfFaceName, (LPCWSTR)"\0");
    if( TYPE( font->vname ) == T_ARRAY )
    {
        /* 存在するフォントの検索 */
        for( i = 0; i < RARRAY_LEN( font->vname ); i++ )
        {
            if( Font_exist( cFont, RARRAY_PTR( font->vname )[i] ) == Qtrue )
            {
#ifdef HAVE_RB_ENC_STR_NEW
                vwidestr = rb_funcall( RARRAY_PTR( font->vname )[i], rb_intern( "encode" ), 1, rb_str_new2( "UTF-16LE" ) );
#else
                {
                    char *buf;
                    int bufsize;
                    bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( RARRAY_PTR( font->vname )[i] ), RSTRING_LEN( RARRAY_PTR( font->vname )[i] ), 0, 0);
                    buf = alloca(bufsize * 2);
                    MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( RARRAY_PTR( font->vname )[i] ), RSTRING_LEN( RARRAY_PTR( font->vname )[i] ), (LPWSTR)buf, bufsize);
                    vwidestr = rb_str_new( buf, bufsize*2 );
                }
#endif
                widestr = alloca( RSTRING_LEN( vwidestr ) + 2 );
                ZeroMemory( widestr, RSTRING_LEN( vwidestr ) + 2 );
                memcpy( widestr, RSTRING_PTR( vwidestr ), RSTRING_LEN( vwidestr ) );
                lstrcpyW( logfont.lfFaceName, widestr );
                break;
            }
        }
    }
    else if( TYPE( font->vname ) == T_STRING )
    {
#ifdef HAVE_RB_ENC_STR_NEW
        vwidestr = rb_funcall( font->vname, rb_intern( "encode" ), 1, rb_str_new2( "UTF-16LE" ) );
#else
        {
            char *buf;
            int bufsize;
            bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( font->vname ), RSTRING_LEN( font->vname ), 0, 0);
            buf = alloca(bufsize * 2);
            MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( font->vname ), RSTRING_LEN( font->vname ), (LPWSTR)buf, bufsize);
            vwidestr = rb_str_new( buf, bufsize*2 );
        }
#endif
        widestr = alloca( RSTRING_LEN( vwidestr ) + 2 );
        ZeroMemory( widestr, RSTRING_LEN( vwidestr ) + 2 );
        memcpy( widestr, RSTRING_PTR( vwidestr ), RSTRING_LEN( vwidestr ) );
        lstrcpyW( logfont.lfFaceName, widestr );
    }

    hFont = CreateFontIndirectW( &logfont );

    if( hFont == NULL )
    {
        rb_raise( eFreeRGSSError, "failed to create font - CreateFontIndirect" );
    }

    /* 描画文字のUTF16LE化 */
#ifdef HAVE_RB_ENC_STR_NEW
    vwidestr = rb_funcall( vstr, rb_intern( "encode" ), 1, rb_str_new2( "UTF-16LE" ) );
#else
    {
        char *buf;
        int bufsize;
        bufsize = MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vstr ), RSTRING_LEN( vstr ), 0, 0);
        buf = alloca(bufsize * 2);
        MultiByteToWideChar(CP_UTF8, 0, RSTRING_PTR( vstr ), RSTRING_LEN( vstr ), (LPWSTR)buf, bufsize);
        vwidestr = rb_str_new( buf, bufsize*2 );
    }
#endif
    widestr = alloca( RSTRING_LEN( vwidestr ) + 2 );
    ZeroMemory( widestr, RSTRING_LEN( vwidestr ) + 2 );
    memcpy( widestr, RSTRING_PTR( vwidestr ), RSTRING_LEN( vwidestr ) );

    hDC = GetDC( g_hWnd );
    SelectObject( hDC, hFont );

    tx = 0;
    for( i = 0; i < RSTRING_LEN( vwidestr ) / 2; i++ )
    {
        GetGlyphOutlineW( hDC, *(widestr + i), GGO_GRAY8_BITMAP,
                          &gm, 0, NULL, &mat2 );
        tx += gm.gmCellIncX;
    }

    DeleteObject( hFont );
    ReleaseDC( g_hWnd, hDC );

    vrect = Rect_allocate( cRect );
    vrect = Rect_initialize( vrect, INT2FIX( 0 ), INT2FIX( 0 ), INT2FIX( tx ), font->vsize );
    return vrect;
}


/*********************************************************************
 * Viewportクラス
 *
 * 描画範囲情報を保持するクラス。
 *********************************************************************/
/*--------------------------------------------------------------------
   参照されなくなったときにGCから呼ばれる関数
 ---------------------------------------------------------------------*/
static void release_Viewport( struct FR_Viewport* vp )
{
    vp->z = 1; /* 最適化により関数がまとめられることの対策 */
    free( vp );
}

/*--------------------------------------------------------------------
   Viewportのmark関数
 ---------------------------------------------------------------------*/
static void mark_Viewport( struct FR_Viewport *vp )
{
    rb_gc_mark( vp->vrect );
    rb_gc_mark( vp->vcolor );
    rb_gc_mark( vp->vtone );
    rb_gc_mark( vp->vsprites );
}

/*--------------------------------------------------------------------
   Viewportクラスのallocate。メモリを確保する為にinitialize前に呼ばれる。
 ---------------------------------------------------------------------*/
static VALUE Viewport_allocate( VALUE klass )
{
    struct FR_Viewport *vp;
    int i;
    VALUE obj;

    /* メモリ取得＆Viewportオブジェクト生成 */
    vp = malloc(sizeof(struct FR_Viewport));
    if( vp == NULL ) rb_raise( eFreeRGSSError, "failed to allocate memory - Viewport_allocate" );

    vp->vrect = Qnil;
    vp->vcolor = Qnil;
    vp->vtone = Qnil;
    vp->vsprites = Qnil;
    obj = Data_Wrap_Struct(klass, mark_Viewport, release_Viewport, vp);

    vp->internal_draw = Viewport_internal_draw;
    vp->vdispose = Qfalse;
    vp->vrect = Rect_allocate( cRect );
    vp->y = 0;
    vp->z = 0;
    vp->vvisible = Qtrue;
    vp->ox = 0;
    vp->oy = 0;
    vp->vcolor = Color_allocate( cColor );
    vp->vtone = Tone_allocate( cTone );
    vp->flash_count = 0;
    vp->flash_count_start = 0;
    vp->flash_red = 0;
    vp->flash_green = 0;
    vp->flash_blue = 0;
    vp->flash_alpha = 0;
    vp->vsprites = rb_ary_new();

    return obj;
}

/*--------------------------------------------------------------------
   ViewportクラスのInitialize
 ---------------------------------------------------------------------*/
static VALUE Viewport_initialize( int argc, VALUE *argv, VALUE self )
{
    struct FR_Viewport *vp = FR_GET_STRUCT( Viewport, self );
    VALUE arg1, arg2, arg3, arg4;
    struct FR_Rect *rect;

    rb_scan_args( argc, argv, "13", &arg1, &arg2, &arg3, &arg4 );
    Data_Get_Struct( vp->vrect, struct FR_Rect, rect );

    if( TYPE( arg1 ) == T_FIXNUM )
    {
        rect->x = NUM2INT( arg1 );
        rect->y = NUM2INT( arg2 );
        rect->width = NUM2INT( arg3 );
        rect->height = NUM2INT( arg4 );
    }
    else
    {
        FR_CHECK_TYPE( Rect, arg1 );
        Rect_copy( vp->vrect, arg1 );
    }

    vp->y = rect->y;

    rb_ary_push( g_graphics.vsprites, self );

    return self;
}

static VALUE Viewport_dispose( VALUE self )
{
    FR_GET_STRUCT( Viewport, self )->vdispose = Qtrue;
    rb_ary_delete( g_graphics.vsprites, self );
    return self;
}
static VALUE Viewport_get_dispose( VALUE self )
{
    return FR_GET_STRUCT( Viewport, self )->vdispose;
}

static VALUE Viewport_flash( VALUE self, VALUE vcolor, VALUE vcount )
{
    struct FR_Viewport *viewport = FR_GET_STRUCT( Viewport, self );
    struct FR_Color *color;

    if( vcolor == Qnil )
    {
        viewport->flash_delete = 1;
    }
    else
    {
        FR_CHECK_TYPE( Color, vcolor );
        Data_Get_Struct( vcolor, struct FR_Color, color );
        viewport->flash_red = color->red;
        viewport->flash_green = color->green;
        viewport->flash_blue = color->blue;
        viewport->flash_alpha = color->alpha;
        viewport->flash_delete = 0;
    }

    viewport->flash_count = viewport->flash_count_start = NUM2INT( vcount );
 
    return self;
}

static VALUE Viewport_update( VALUE self )
{
    struct FR_Viewport *viewport = FR_GET_STRUCT( Viewport, self );
    if( viewport->flash_count > 0 )
    {
        viewport->flash_count--;
    }
    return self;
}

static VALUE Viewport_set_z( VALUE self, VALUE vz )
{
    FR_GET_STRUCT( Viewport, self )->z = NUM2INT( vz );
    return vz;
}
static VALUE Viewport_get_z( VALUE self )
{
    return INT2FIX( FR_GET_STRUCT( Viewport, self )->z );
}
static VALUE Viewport_set_ox( VALUE self, VALUE vox )
{
    FR_GET_STRUCT( Viewport, self )->ox = NUM2INT( vox );
    return vox;
}
static VALUE Viewport_get_ox( VALUE self )
{
    return INT2FIX( FR_GET_STRUCT( Viewport, self )->ox );
}
static VALUE Viewport_set_oy( VALUE self, VALUE voy )
{
    FR_GET_STRUCT( Viewport, self )->oy = NUM2INT( voy );
    return voy;
}
static VALUE Viewport_get_oy( VALUE self )
{
    return INT2FIX( FR_GET_STRUCT( Viewport, self )->oy );
}
static VALUE Viewport_set_rect( VALUE self, VALUE vrect )
{
    Rect_copy( FR_GET_STRUCT( Viewport, self )->vrect, vrect );
    return vrect;
}
static VALUE Viewport_get_rect( VALUE self )
{
    return FR_GET_STRUCT( Viewport, self )->vrect;
}
static VALUE Viewport_set_color( VALUE self, VALUE vcolor )
{
    Color_copy( FR_GET_STRUCT( Viewport, self )->vcolor, vcolor );
    return vcolor;
}
static VALUE Viewport_get_color( VALUE self )
{
    return FR_GET_STRUCT( Viewport, self )->vcolor;
}
static VALUE Viewport_set_tone