#pragma once

// To be used by external Grout applications
// Makes possible the use of #include <Grout.h>

#include "Grout/Core/Application.h"
#include "Grout/Core/Layer.h"
#include "Grout/Core/Log.h"
#include "Grout/Core/Time.h"

// ------------ Input related ------------
#include "Grout/Core/Input.h"
#include "Grout/Core/MouseCodes.h"
#include "Grout/Core/KeyCodes.h"
// ----------------------------------


// ------------ Interface ------------
#include "Grout/ImGui/ImGuiLayer.h"
// ----------------------------------


// ------------ Renderer --------------
#include "Grout/Renderer/Renderer.h"
#include "Grout/Renderer/RenderCommand.h"

#include "Grout/Renderer/VertexArray.h"
#include "Grout/Renderer/Shader.h"
#include "Grout/Renderer/Texture.h"
#include "Grout/Renderer/Buffer.h"

#include "Grout/Renderer/Camera.h"

#include "Grout/Renderer/Components.h"
// ----------------------------------


// ------------ Scene data --------------
#include "Grout/Scene/Object.h"
#include "Grout/Scene/Transform.h"
// ----------------------------------

// --------- Entry Point -----------
#include "Grout/Core/EntryPoint.h"
// ---------------------------------