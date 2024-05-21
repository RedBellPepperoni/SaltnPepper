#include "Window.hpp"

namespace SaltnPepperEngine
{
    

    NODISCARD Rect2D<int> Window::GetSize() const noexcept
    {
        return  Rect2D<int>();
    }

    void Window::SetSize(Rect2D<int> NewSize) noexcept
    {
    }
    NODISCARD std::string_view Window::GetTitle() const noexcept
    {
        return  std::string_view();
    }
    void Window::SetTitle(std::string_view NewTitle) noexcept
    {
    }
    NODISCARD bool Window::IsBorderless() const noexcept
    {
        return  bool();
    }
    void Window::SetBorderless(bool Borderless) const noexcept
    {
    }
    NODISCARD bool Window::IsCursorHidden() noexcept
    {
        return bool();
    }
    void Window::SetCursorHidden() noexcept
    {
    }
}