#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core/EngineDefines.hpp"
#include "PlatformDefinitions.hpp"

namespace SaltnPepperEngine
{
	class SNP_API Application 
	{
		friend class Editor;
		friend class Runtime;

	public:

		/// <summary>
		/// Constructor This should really not be used for anything
		/// </summary>
		Application();

		/// <summary>
		/// Destructor : For Classes that Inherit the system
		/// </summary>
		virtual ~Application();

		/// <summary>
		/// Use this to Run the application 
		/// </summary>
		void Run();

		/// <summary>
		/// Function to initilize all the application crucial data before the actual application is run
		/// </summary>
		virtual void OnInit();

		/// <summary>
		/// Function where the updates gets executed once per frame (Framerate dependant)
		/// </summary>
		virtual void OnUpdate();

		/// <summary>
		/// Function where the updates get executed in a fixed delta time step (Framerate Independant)
		/// </summary>
		virtual void OnFixedUpdate();

		/// <summary>
		/// Function where the Render updates are called (Render to offscreen buffers)
		/// </summary>
		virtual void OnRender();

		/// <summary>
		/// Final render to the screen
		/// </summary>
		virtual void OnPresent();

		/// <summary>
		/// Defines what happens when the window size is changed
		/// </summary>
		virtual void OnSizeChanged(unsigned int newWidth, unsigned int newHeight, bool minimized);



		const unsigned int GetWindowWidth() const;
		const unsigned int GetWindowHeight() const;




	protected:

		

		


	};

}


#endif // !APPLICATION_H

