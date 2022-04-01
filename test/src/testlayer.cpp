#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>
#include <rendering/renderer.h>

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
    0, 1, 2,
    1, 3, 2,
    4, 6, 5,
    5, 6, 7,
    0, 2, 4,
    4, 2, 6,
    1, 5, 3,
    5, 7, 3,
    0, 4, 1,
    4, 5, 1,
    2, 3, 6,
    6, 3, 7,
};

TestLayer::TestLayer() {
    //nothing		
}

void TestLayer::update() {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }

	if(Input::isKeyPressed(D)) {
		position.x += 0.01f;
	}

	if(Input::isKeyPressed(A)) {
		position.x -= 0.01f;
	}

	if(Input::isKeyPressed(W)) {
		position.z += 0.01f;
	}

	if(Input::isKeyPressed(S)) {
		position.z -= 0.01f;
	}

	const bx::Vec3 at = position;
	const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};

	float view[16];
	bx::mtxLookAt(view, eye, at);
	bx::mtxTranslate(view, -position.x, -position.y, -position.z+5.0f);
	float proj[16];
	bx::mtxProj(proj, 60.0f, (float)Application::get().getWindow().width/(float)Application::get().getWindow().height, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);
	float mtx[16];
	bx::mtxRotateXYZ(mtx, 45, 45, 45);
	bgfx::setTransform(mtx);

	bgfx::setVertexBuffer(0, vbh);
	bgfx::setIndexBuffer(ibh);

	bgfx::submit(0, program);
}

void TestLayer::start() {
	bgfx::VertexLayout pcvDecl;
	pcvDecl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();
	
	vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), pcvDecl);
	ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

	vsh = renderer::loadShader("../overture/res/shaders/", "vs_cubes.bin");
	fsh = renderer::loadShader("../overture/res/shaders/", "fs_cubes.bin");

	program = bgfx::createProgram(vsh, fsh, true);

    DEBUG("it works");
}

void TestLayer::end() {
		bgfx::destroy(program);
		bgfx::destroy(ibh);
		bgfx::destroy(vbh);
}
