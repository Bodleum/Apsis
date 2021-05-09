#pragma once

// ---   Core   ---
#include "Apsis/Core/App.h"
#include "Apsis/Core/Core.h"
#include "Apsis/Core/Input.h"
//#include "Apsis/Core/Layer.h"				Included in App.h
#include "Apsis/Core/Logger.h"
//#include "Apsis/Core/Platform.h"			Included in Main.h
//#include "Apsis/Core/SystemInfo.h"		Included in Main.h
#include "Apsis/Core/Window.h"


// ---   Event   ---
//#include "Apsis/Event/Event.h"			Included in EventDispatcher.h
//#include "Apsis/Event/EventDispatcher.h"	Included in Layer.h

// ---   Renderer   ---
#include "Apsis/Renderer/Buffer.h"
#include "Apsis/Renderer/Renderer.h"
//#include "Apsis/Renderer/RendererAPI.h"	Included in SystemInfo.h
//#include "Apsis/Renderer/Shader.h"		Included in Renderer.h
//#include "Apsis/Renderer/Texture.h"		Included in Renderer.h


// ---   Utility   ---
#include "Apsis/Utility/Color.h"
#include "Apsis/Utility/Instrumentor.h"


// ---   Entry Point   ---
// MUST BE LAST
#include "Apsis/Core/Main.h"