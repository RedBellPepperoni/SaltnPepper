#ifndef UTILS_H
#define UTILS_H

namespace SaltnPepperEngine
{
	namespace Math
	{
		/// <summary>
		/// A point in screen coords (2D) with a X and Y component
		/// </summary>
		template <typename T>
		struct Point2D
		{
			T X;
			T Y;
		};

		/// <summary>
		/// A Rectangular area with Width and Height component
		/// </summary>
		template <typename T>
		struct Rect2D
		{
			T Width;
			T Height;
		};

		/// <summary>
		/// Standard Viewport with a screen position and Rect Bounds
		/// </summary>
		template <typename T>
		struct Viewport
		{
			Point2D<unsigned int> Position;
			Rect2D<unsigned int> Bounds;

		};

		/// <summary>
		/// Viewpoet which has its origin centralized
		/// </summary>
		struct CentralizedViewport
		{
			float Top;
			float Right;
			float Bottom;
			float Left;
		};

	}

	using namespace Math;
}


#endif // !UTILS_H
