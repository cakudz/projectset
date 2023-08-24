#include "direct2d.h"
#include "../../windows/windows.h"

// safe release of d2d resources
#define safe_release(x)\
{if (x!=nullptr){ x->Release(); }}

namespace rendering {

	c_rendering g_renderer;

	// called after dispatching messages - every frame
	void c_rendering::run_frame( void ) {

        PAINTSTRUCT ps;
        BeginPaint( windows.g_data.canvas_window, &ps );

        // begins the drawing
        this->m_render_target->BeginDraw( );

        // clears the window
        this->m_render_target->Clear( D2D1::ColorF( 0, 0, 0, 1.f ) );

        /* 
        * below will be where the rendering is done
        * before EndDraw is called
        * -----------------
        * should i have rendertarget helper functions like 'line' and 'triangle' and shape functions in here
        * or another class?
        * every GUI element should be a c_gelement
        */

        auto hr = this->m_render_target->EndDraw( );

        // not exactly how microsoft do it but i see no logical difference
        if ( FAILED( hr ) || hr == D2DERR_RECREATE_TARGET ) {

            this->release_resources( );
            this->allocate_resources( );

        }

        EndPaint( windows.g_data.canvas_window, &ps );

	}

    // no sanity checks, will just allocate new resources
	bool c_rendering::allocate_resources( void ) {
        RECT rc;
        GetClientRect( windows.g_data.canvas_window, &rc );

        D2D1_SIZE_U size = D2D1::SizeU( rc.right, rc.bottom );

        auto hr = m_factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties( ),
            D2D1::HwndRenderTargetProperties( windows.g_data.canvas_window, size ),
            &this->m_render_target );

        if ( SUCCEEDED( hr ) )
        {
            // we have the render target, now make the brushes 

            const D2D1_COLOR_F color = D2D1::ColorF( 1.0f, 1.0f, 0 );
            hr = this->m_render_target->CreateSolidColorBrush( color, &this->m_brushes.m_solid_brush );

            return SUCCEEDED(hr);
        }

        return false;
	}

    bool c_rendering::allocate_const_resources( ) {
        return SUCCEEDED( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->m_factory ) );
    }

    // also no sanity checks, will release all allocated shizz
    void c_rendering::release_resources( ) {     

        // iterate through all brushes no matter if it is x86 or 64 bit
        for ( unsigned int i = 0; i < (sizeof( this->m_brushes ) / sizeof( void* )); i += 1 ) {
            safe_release( reinterpret_cast<ID2D1Brush**>(&this->m_brushes)[ i ] );
            reinterpret_cast<ID2D1Brush**>(&this->m_brushes)[ i ] = nullptr;
        }

        safe_release( this->m_render_target );
        this->m_render_target = nullptr;
    }

    void c_rendering::release_const_resources( ) {
        safe_release( this->m_factory );
        this->m_factory = nullptr;
    }

    bool c_rendering::should_handle( event::type* e ) {

        if ( e->m_category != event::resize_event )
            return false;

        auto event = reinterpret_cast<event::resize_t*>(e);

        // if we have a render target, it needs to be resized 
        // one sanity check because called from wndproc
        if ( this->m_render_target != nullptr ) {

            D2D1_SIZE_U size = D2D1::SizeU( event->height, event->width );

            this->m_render_target->Resize( size );
            InvalidateRect( windows.g_data.canvas_window, NULL, FALSE );
        }

        return false;

    }
}