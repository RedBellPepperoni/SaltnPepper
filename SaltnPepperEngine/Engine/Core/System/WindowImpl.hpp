#ifndef WINDOWIMPL_H
#define WINDOWIMPL_H
#include "Core/System/Window.hpp"

namespace SaltnPepperEngine	
{
	using namespace Memory;

	class SNP_API WindowImpl
	{

	};


	/// Pointer to implementation using C++11 smart Pointer
	/// Need to Define the Window Destructor AFter the Implementation Definition
	Window::Window() : m_windowImpl(MakeUnique<WindowImpl>()) {}

	Window::~Window() = default;
}

#endif // !WINDOWIMPL_H
