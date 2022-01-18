#pragma once

// To be used by external Grout applications
// Makes possible the use of #include <Grout.h>

#include "Grout/Application.h"
#include "Grout/Layer.h"
#include "Grout/Log.h"

// ------------ Input related ------------
#include "Grout/Input.h"
#include "Grout/MouseButtonCodes.h"
#include "Grout/KeyCodes.h"
// ----------------------------------


// ------------ Interface ------------
#include "Grout/ImGui/ImGuiLayer.h"
// ----------------------------------


// ------------ Renderer --------------
#include "Grout/Renderer/Renderer.h"
#include "Grout/Renderer/RenderCommand.h"

#include "Grout/Renderer/VertexArray.h"
#include "Grout/Renderer/Shader.h"
#include "Grout/Renderer/Buffer.h"

#include "Grout/Renderer/Camera.h"
// ----------------------------------


// --------- Entry Point -----------
#include "Grout/EntryPoint.h"
// ---------------------------------