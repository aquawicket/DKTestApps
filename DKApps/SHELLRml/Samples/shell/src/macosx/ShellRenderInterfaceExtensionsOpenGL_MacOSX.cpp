/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <ShellRenderInterfaceExtensions.h>
#include <ShellRenderInterfaceOpenGL.h>
#include <Carbon/Carbon.h>
#include <RmlUi/Core/Platform.h>
#include <RmlUi/Core/Types.h>

void ShellRenderInterfaceOpenGL::SetViewport(int width, int height)
{
	if(m_width != width || m_height != height) {
		Rml::Matrix4f projection, view;

		m_width = width;
		m_height = height;

		glViewport(0, 0, width, height);
		projection = Rml::Matrix4f::ProjectOrtho(0, (float)width, (float)height, 0, -10000, 10000);
		glMatrixMode(GL_PROJECTION);
        //glLoadMatrixf(projection);
		view = Rml::Matrix4f::Identity();
		glMatrixMode(GL_MODELVIEW);
        //glLoadMatrixf(view);

		//aglUpdateContext(gl_context);
        
	}
}

bool ShellRenderInterfaceOpenGL::AttachToNative(void *nativeWindow)
{
    /*
	WindowRef window = (WindowRef)nativeWindow;
	static GLint attributes[] =
	{
		GL_RGBA,
		GL_DOUBLEBUFFER,
		GLFW_ALPHA_BITS, 8,
        GLFW_DEPTH_BITS, 24,
		GLFW_STENCIL_BITS, 8,
		GLFW_ACCELERATED,
		GL_NONE
	};
	
	AGLPixelFormat pixel_format = aglChoosePixelFormat(nullptr, 0, attributes);
	if (pixel_format == nullptr)
		return false;
	
    //CGrafPtr window_port = window;//GetWindowPort(window);
	//if (window_port == nullptr)
	//	return false;
	*/
	//this->gl_context = aglCreateContext(pixel_format, nullptr);
    this->gl_context = (GLFWwindow*)nativeWindow;
    if (this->gl_context == nullptr)
		return false;
	
	//aglSetDrawable(this->gl_context, window_port);
    //aglSetCurrentContext(this->gl_context);
    glfwMakeContextCurrent(this->gl_context);
    
	//aglDestroyPixelFormat(pixel_format);

    // Used to avoid screen tearing
    glfwSwapInterval(1);

	
	// Set up the GL state.
	glClearColor(0, 0, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    int left, top, right, bottom;
    glfwGetWindowFrameSize((GLFWwindow*)nativeWindow, &left, &top, &right, &bottom);
	//Rect crect;
	//GetWindowBounds(window, kWindowContentRgn, &crect);
	glOrtho(0, (right - left), (bottom - top), 0, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ShellRenderInterfaceOpenGL::DetachFromNative()
{
	// Shutdown OpenGL if necessary.
	//aglSetCurrentContext(nullptr);
    glfwMakeContextCurrent(nullptr);
    
	//aglSetDrawable(this->gl_context, nullptr);
	//aglDestroyContext(this->gl_context);
}

void ShellRenderInterfaceOpenGL::PrepareRenderBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void ShellRenderInterfaceOpenGL::PresentRenderBuffer()
{
	// Flips the OpenGL buffers.
	//aglSwapBuffers(this->gl_context);
    glfwSwapBuffers(this->gl_context);
}
