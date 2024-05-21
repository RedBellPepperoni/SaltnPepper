#ifndef WINDOW_H
#include "Core/EngineDefines.hpp"
#include "Utilities/Math/Utils.hpp"
#include <string>
#include "Core/Memory/MemoryDefinitions.hpp"

namespace SaltnPepperEngine
{
	using namespace Memory;

	class  WindowImpl;  

	class SNP_API Window
	{
	

	public:

		explicit Window();
		~Window();
		
		NONCOPYABLEANDMOVE(Window)

		/// <summary>
		/// Returns the Window Handle as a void ptr
		/// </summary>
		NODISCARD void* GetHandle() const noexcept;

		/// <summary>
		/// Returns the size of the window as a Rect2D (with width and height)
		/// </summary>
		/// <returns></returns>
		NODISCARD Rect2D<int> GetSize() const noexcept;

		/// <summary>
		/// Sets the Window to the new desired size
		/// </summary>
		/// <param name="NewSize"></param>
		void SetSize(Rect2D<int> NewSize) noexcept;


		/// <summary>
		/// Returns the Window title as a wtring view 
		/// </summary>
		NODISCARD std::string_view GetTitle() const noexcept;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="NewTitle"></param>
		void SetTitle(std::string_view NewTitle) noexcept;

		/// <summary>
		///  <para> Get whether the Window is Borderless or Fullscreen </para>
		///  <para> true  : borderless </para>
		///  <para> false : fullscreen </para>
		/// </summary>
		/// <returns></returns>
		NODISCARD bool IsBorderless() const noexcept;

		/// <summary>
		///  <para> Set the window to render as borderless or fullscreen </para>
		///  <para> true  : borderless </para>
		///  <para> false : fullscreen </para>
		/// </summary>
		void SetBorderless(bool Borderless) const noexcept;

		/// <summary>
		///  <para> Get the Cursor Render State </para>
		///  <para> true :  Hidden </para>
		///  <para> false :  Visible </para>
		/// </summary>
		NODISCARD bool IsCursorHidden() noexcept;

		/// <summary>
		///<para> Sets the Cursor Render State < / para>
		///  <para> true  :  Hidden </para>
		///  <para> false :  Visible </para>
		/// </summary>
		void SetCursorHidden() noexcept;

	private:

		/// <summary>
		///  The Pointer Implementaion of Window
		/// </summary>
		UniquePtr<WindowImpl> m_windowImpl;

	};
}

#endif // !WINDOW_H
