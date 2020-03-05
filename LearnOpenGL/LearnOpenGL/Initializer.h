#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Camera.h"
#include "GLObject.h"
#include "GLLightObject.h"
#include "GLDirectionLight.h"
#include "GLSpotLight.h"
#include "GLPointLight.h"
#include "GLSimpleCube.h"
#include "GLSimpleLight.h"
#include "GLSimpleMaterial.h"
#include "GLSimpleTexture.h"
#include "GLLightMapCube.h"
#include "GLFrameCube.h"
#include "GLCubeBorder.h"
#include "GLAlphaTexture.h"
#include "GLBlendingTexture.h"
#include "OffScreenRenderer.h"
#include "GLPostProcessingRect.h"
#include "GLSkyBox.h"

class Initializer {
public:
	static void initialize();
};