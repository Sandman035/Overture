#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>
#include <rendering/renderer.h>

/*
static renderer::PosColorVertex cubeVertices[] =
{
	{ 1.40000f,  0.00000f, 2.40000f, 0xffffffff},
	{ 1.40000f, -0.78400f, 2.40000f, 0xffffffff},
	{ 0.78000f, -1.40000f, 2.40000f, 0xffffffff},
	{ 0.00000f, -1.40000f, 2.40000f, 0xffffffff},
	{ 1.33750f,  0.00000f, 2.53125f, 0xffffffff},
	{ 1.33750f, -0.74900f, 2.53125f, 0xffffffff},
	{ 0.74900f, -1.33750f, 2.53125f, 0xffffffff},
	{ 0.00000f, -1.33750f, 2.53125f, 0xffffffff},
	{ 1.43750f,  0.00000f, 2.53125f, 0xffffffff},
	{ 1.43750f, -0.80500f, 2.53125f, 0xffffffff},
	{ 0.80500f, -1.43750f, 2.53125f, 0xffffffff},
	{ 0.00000f, -1.43750f, 2.53125f, 0xffffffff},
	{ 1.50000f,  0.00000f, 2.40000f, 0xffffffff},
	{ 1.50000f, -0.84000f, 2.40000f, 0xffffffff},
	{ 0.84000f, -1.50000f, 2.40000f, 0xffffffff},
	{ 0.00000f, -1.50000f, 2.40000f, 0xffffffff},
	{-0.78400f, -1.40000f, 2.40000f, 0xffffffff},
	{-1.40000f, -0.78400f, 2.40000f, 0xffffffff},
	{-1.40000f,  0.00000f, 2.40000f, 0xffffffff},
	{-0.74900f, -1.33750f, 2.53125f, 0xffffffff},
	{-1.33750f, -0.74900f, 2.53125f, 0xffffffff},
	{-1.33750f,  0.00000f, 2.53125f, 0xffffffff},
	{-0.80500f, -1.43750f, 2.53125f, 0xffffffff},
	{-1.43750f, -0.80500f, 2.53125f, 0xffffffff},
	{-1.43750f,  0.00000f, 2.53125f, 0xffffffff},
	{-0.84000f, -1.50000f, 2.40000f, 0xffffffff},
	{-1.50000f, -0.84000f, 2.40000f, 0xffffffff},
	{-1.50000f,  0.00000f, 2.40000f, 0xffffffff},
	{-1.40000f,  0.78400f, 2.40000f, 0xffffffff},
	{-0.78400f,  1.40000f, 2.40000f, 0xffffffff},
	{ 0.00000f,  1.40000f, 2.40000f, 0xffffffff},
	{-1.33750f,  0.74900f, 2.53125f, 0xffffffff},
	{-0.74900f,  1.33750f, 2.53125f, 0xffffffff},
	{ 0.00000f,  1.33750f, 2.53125f, 0xffffffff},
	{-1.43750f,  0.80500f, 2.53125f, 0xffffffff},
	{-0.80500f,  1.43750f, 2.53125f, 0xffffffff},
	{ 0.00000f,  1.43750f, 2.53125f, 0xffffffff},
	{-1.50000f,  0.84000f, 2.40000f, 0xffffffff},
	{-0.84000f,  1.50000f, 2.40000f, 0xffffffff},
	{ 0.00000f,  1.50000f, 2.40000f, 0xffffffff},
	{ 0.78400f,  1.40000f, 2.40000f, 0xffffffff},
	{ 1.40000f,  0.78400f, 2.40000f, 0xffffffff},
	{ 0.74900f,  1.33750f, 2.53125f, 0xffffffff},
	{ 1.33750f,  0.74900f, 2.53125f, 0xffffffff},
	{ 0.80500f,  1.43750f, 2.53125f, 0xffffffff},
	{ 1.43750f,  0.80500f, 2.53125f, 0xffffffff},
	{ 0.84000f,  1.50000f, 2.40000f, 0xffffffff},
	{ 1.50000f,  0.84000f, 2.40000f, 0xffffffff},
	{ 1.75000f,  0.00000f, 1.87500f, 0xffffffff},
	{ 1.75000f, -0.98000f, 1.87500f, 0xffffffff},
	{ 0.98000f, -1.75000f, 1.87500f, 0xffffffff},
	{ 0.00000f, -1.75000f, 1.87500f, 0xffffffff},
	{ 2.00000f,  0.00000f, 1.35000f, 0xffffffff},
	{ 2.00000f, -1.12000f, 1.35000f, 0xffffffff},
	{ 1.12000f, -2.00000f, 1.35000f, 0xffffffff},
	{ 0.00000f, -2.00000f, 1.35000f, 0xffffffff},
	{ 2.00000f,  0.00000f, 0.90000f, 0xffffffff},
	{ 2.00000f, -1.12000f, 0.90000f, 0xffffffff},
	{ 1.12000f, -2.00000f, 0.90000f, 0xffffffff},
	{ 0.00000f, -2.00000f, 0.90000f, 0xffffffff},
	{-0.98000f, -1.75000f, 1.87500f, 0xffffffff},
	{-1.75000f, -0.98000f, 1.87500f, 0xffffffff},
	{-1.75000f,  0.00000f, 1.87500f, 0xffffffff},
	{-1.12000f, -2.00000f, 1.35000f, 0xffffffff},
	{-2.00000f, -1.12000f, 1.35000f, 0xffffffff},
	{-2.00000f,  0.00000f, 1.35000f, 0xffffffff},
	{-1.12000f, -2.00000f, 0.90000f, 0xffffffff},
	{-2.00000f, -1.12000f, 0.90000f, 0xffffffff},
	{-2.00000f,  0.00000f, 0.90000f, 0xffffffff},
	{-1.75000f,  0.98000f, 1.87500f, 0xffffffff},
	{-0.98000f,  1.75000f, 1.87500f, 0xffffffff},
	{ 0.00000f,  1.75000f, 1.87500f, 0xffffffff},
	{-2.00000f,  1.12000f, 1.35000f, 0xffffffff},
	{-1.12000f,  2.00000f, 1.35000f, 0xffffffff},
	{ 0.00000f,  2.00000f, 1.35000f, 0xffffffff},
	{-2.00000f,  1.12000f, 0.90000f, 0xffffffff},
	{-1.12000f,  2.00000f, 0.90000f, 0xffffffff},
	{ 0.00000f,  2.00000f, 0.90000f, 0xffffffff},
	{ 0.98000f,  1.75000f, 1.87500f, 0xffffffff},
	{ 1.75000f,  0.98000f, 1.87500f, 0xffffffff},
	{ 1.12000f,  2.00000f, 1.35000f, 0xffffffff},
	{ 2.00000f,  1.12000f, 1.35000f, 0xffffffff},
	{ 1.12000f,  2.00000f, 0.90000f, 0xffffffff},
	{ 2.00000f,  1.12000f, 0.90000f, 0xffffffff},
	{ 2.00000f,  0.00000f, 0.45000f, 0xffffffff},
	{ 2.00000f, -1.12000f, 0.45000f, 0xffffffff},
	{ 1.12000f, -2.00000f, 0.45000f, 0xffffffff},
	{ 0.00000f, -2.00000f, 0.45000f, 0xffffffff},
	{ 1.50000f,  0.00000f, 0.22500f, 0xffffffff},
	{ 1.50000f, -0.84000f, 0.22500f, 0xffffffff},
	{ 0.84000f, -1.50000f, 0.22500f, 0xffffffff},
	{ 0.00000f, -1.50000f, 0.22500f, 0xffffffff},
	{ 1.50000f,  0.00000f, 0.15000f, 0xffffffff},
	{ 1.50000f, -0.84000f, 0.15000f, 0xffffffff},
	{ 0.84000f, -1.50000f, 0.15000f, 0xffffffff},
	{ 0.00000f, -1.50000f, 0.15000f, 0xffffffff},
	{-1.12000f, -2.00000f, 0.45000f, 0xffffffff},
	{-2.00000f, -1.12000f, 0.45000f, 0xffffffff},
	{-2.00000f,  0.00000f, 0.45000f, 0xffffffff},
	{-0.84000f, -1.50000f, 0.22500f, 0xffffffff},
	{-1.50000f, -0.84000f, 0.22500f, 0xffffffff},
	{-1.50000f,  0.00000f, 0.22500f, 0xffffffff},
	{-0.84000f, -1.50000f, 0.15000f, 0xffffffff},
	{-1.50000f, -0.84000f, 0.15000f, 0xffffffff},
	{-1.50000f,  0.00000f, 0.15000f, 0xffffffff},
	{-2.00000f,  1.12000f, 0.45000f, 0xffffffff},
	{-1.12000f,  2.00000f, 0.45000f, 0xffffffff},
	{ 0.00000f,  2.00000f, 0.45000f, 0xffffffff},
	{-1.50000f,  0.84000f, 0.22500f, 0xffffffff},
	{-0.84000f,  1.50000f, 0.22500f, 0xffffffff},
	{ 0.00000f,  1.50000f, 0.22500f, 0xffffffff},
	{-1.50000f,  0.84000f, 0.15000f, 0xffffffff},
	{-0.84000f,  1.50000f, 0.15000f, 0xffffffff},
	{ 0.00000f,  1.50000f, 0.15000f, 0xffffffff},
	{ 1.12000f,  2.00000f, 0.45000f, 0xffffffff},
	{ 2.00000f,  1.12000f, 0.45000f, 0xffffffff},
	{ 0.84000f,  1.50000f, 0.22500f, 0xffffffff},
	{ 1.50000f,  0.84000f, 0.22500f, 0xffffffff},
	{ 0.84000f,  1.50000f, 0.15000f, 0xffffffff},
	{ 1.50000f,  0.84000f, 0.15000f, 0xffffffff},
	{-1.60000f,  0.00000f, 0.02500f, 0xffffffff},
	{-1.60000f, -0.30000f, 2.02500f, 0xffffffff},
	{-1.50000f, -0.30000f, 2.25000f, 0xffffffff},
	{-1.50000f,  0.00000f, 2.25000f, 0xffffffff},
	{-2.30000f,  0.00000f, 2.02500f, 0xffffffff},
	{-2.30000f, -0.30000f, 2.02500f, 0xffffffff},
	{-2.50000f, -0.30000f, 2.25000f, 0xffffffff},
	{-2.50000f,  0.00000f, 2.25000f, 0xffffffff},
	{-2.70000f,  0.00000f, 2.02500f, 0xffffffff},
	{-2.70000f, -0.30000f, 2.02500f, 0xffffffff},
	{-3.00000f, -0.30000f, 2.25000f, 0xffffffff},
	{-3.00000f,  0.00000f, 2.25000f, 0xffffffff},
	{-2.70000f,  0.00000f, 1.80000f, 0xffffffff},
	{-2.70000f, -0.30000f, 1.80000f, 0xffffffff},
	{-3.00000f, -0.30000f, 1.80000f, 0xffffffff},
	{-3.00000f,  0.00000f, 1.80000f, 0xffffffff},
	{-1.50000f,  0.30000f, 2.25000f, 0xffffffff},
	{-1.60000f,  0.30000f, 2.02500f, 0xffffffff},
	{-2.50000f,  0.30000f, 2.25000f, 0xffffffff},
	{-2.30000f,  0.30000f, 2.02500f, 0xffffffff},
	{-3.00000f,  0.30000f, 2.25000f, 0xffffffff},
	{-2.70000f,  0.30000f, 2.02500f, 0xffffffff},
	{-3.00000f,  0.30000f, 1.80000f, 0xffffffff},
	{-2.70000f,  0.30000f, 1.80000f, 0xffffffff},
	{-2.70000f,  0.00000f, 1.57500f, 0xffffffff},
	{-2.70000f, -0.30000f, 1.57500f, 0xffffffff},
	{-3.00000f, -0.30000f, 1.35000f, 0xffffffff},
	{-3.00000f,  0.00000f, 1.35000f, 0xffffffff},
	{-2.50000f,  0.00000f, 1.12500f, 0xffffffff},
	{-2.50000f, -0.30000f, 1.12500f, 0xffffffff},
	{-2.65000f, -0.30000f, 0.93750f, 0xffffffff},
	{-2.65000f,  0.00000f, 0.93750f, 0xffffffff},
	{-2.00000f, -0.30000f, 0.90000f, 0xffffffff},
	{-1.90000f, -0.30000f, 0.60000f, 0xffffffff},
	{-1.90000f,  0.00000f, 0.60000f, 0xffffffff},
	{-3.00000f,  0.30000f, 1.35000f, 0xffffffff},
	{-2.70000f,  0.30000f, 1.57500f, 0xffffffff},
	{-2.65000f,  0.30000f, 0.93750f, 0xffffffff},
	{-2.50000f,  0.30000f, 1.12500f, 0xffffffff},
	{-1.90000f,  0.30000f, 0.60000f, 0xffffffff},
	{-2.00000f,  0.30000f, 0.90000f, 0xffffffff},
	{ 1.70000f,  0.00000f, 1.42500f, 0xffffffff},
	{ 1.70000f, -0.66000f, 1.42500f, 0xffffffff},
	{ 1.70000f, -0.66000f, 0.60000f, 0xffffffff},
	{ 1.70000f,  0.00000f, 0.60000f, 0xffffffff},
	{ 2.60000f,  0.00000f, 1.42500f, 0xffffffff},
	{ 2.60000f, -0.66000f, 1.42500f, 0xffffffff},
	{ 3.10000f, -0.66000f, 0.82500f, 0xffffffff},
	{ 3.10000f,  0.00000f, 0.82500f, 0xffffffff},
	{ 2.30000f,  0.00000f, 2.10000f, 0xffffffff},
	{ 2.30000f, -0.25000f, 2.10000f, 0xffffffff},
	{ 2.40000f, -0.25000f, 2.02500f, 0xffffffff},
	{ 2.40000f,  0.00000f, 2.02500f, 0xffffffff},
	{ 2.70000f,  0.00000f, 2.40000f, 0xffffffff},
	{ 2.70000f, -0.25000f, 2.40000f, 0xffffffff},
	{ 3.30000f, -0.25000f, 2.40000f, 0xffffffff},
	{ 3.30000f,  0.00000f, 2.40000f, 0xffffffff},
	{ 1.70000f,  0.66000f, 0.60000f, 0xffffffff},
	{ 1.70000f,  0.66000f, 1.42500f, 0xffffffff},
	{ 3.10000f,  0.66000f, 0.82500f, 0xffffffff},
	{ 2.60000f,  0.66000f, 1.42500f, 0xffffffff},
	{ 2.40000f,  0.25000f, 2.02500f, 0xffffffff},
	{ 2.30000f,  0.25000f, 2.10000f, 0xffffffff},
	{ 3.30000f,  0.25000f, 2.40000f, 0xffffffff},
	{ 2.70000f,  0.25000f, 2.40000f, 0xffffffff},
	{ 2.80000f,  0.00000f, 2.47500f, 0xffffffff},
	{ 2.80000f, -0.25000f, 2.47500f, 0xffffffff},
	{ 3.52500f, -0.25000f, 2.49375f, 0xffffffff},
	{ 3.52500f,  0.00000f, 2.49375f, 0xffffffff},
	{ 2.90000f,  0.00000f, 2.47500f, 0xffffffff},
	{ 2.90000f, -0.15000f, 2.47500f, 0xffffffff},
	{ 3.45000f, -0.15000f, 2.51250f, 0xffffffff},
	{ 3.45000f,  0.00000f, 2.51250f, 0xffffffff},
	{ 2.80000f,  0.00000f, 2.40000f, 0xffffffff},
	{ 2.80000f, -0.15000f, 2.40000f, 0xffffffff},
	{ 3.20000f, -0.15000f, 2.40000f, 0xffffffff},
	{ 3.20000f,  0.00000f, 2.40000f, 0xffffffff},
	{ 3.52500f,  0.25000f, 2.49375f, 0xffffffff},
	{ 2.80000f,  0.25000f, 2.47500f, 0xffffffff},
	{ 3.45000f,  0.15000f, 2.51250f, 0xffffffff},
	{ 2.90000f,  0.15000f, 2.47500f, 0xffffffff},
	{ 3.20000f,  0.15000f, 2.40000f, 0xffffffff},
	{ 2.80000f,  0.15000f, 2.40000f, 0xffffffff},
	{ 0.00000f,  0.00000f, 3.15000f, 0xffffffff},
	{ 0.00000f, -0.00200f, 3.15000f, 0xffffffff},
	{ 0.00200f,  0.00000f, 3.15000f, 0xffffffff},
	{ 0.80000f,  0.00000f, 3.15000f, 0xffffffff},
	{ 0.80000f, -0.45000f, 3.15000f, 0xffffffff},
	{ 0.45000f, -0.80000f, 3.15000f, 0xffffffff},
	{ 0.00000f, -0.80000f, 3.15000f, 0xffffffff},
	{ 0.00000f,  0.00000f, 2.85000f, 0xffffffff},
	{ 0.20000f,  0.00000f, 2.70000f, 0xffffffff},
	{ 0.20000f, -0.11200f, 2.70000f, 0xffffffff},
	{ 0.11200f, -0.20000f, 2.70000f, 0xffffffff},
	{ 0.00000f, -0.20000f, 2.70000f, 0xffffffff},
	{-0.00200f,  0.00000f, 3.15000f, 0xffffffff},
	{-0.45000f, -0.80000f, 3.15000f, 0xffffffff},
	{-0.80000f, -0.45000f, 3.15000f, 0xffffffff},
	{-0.80000f,  0.00000f, 3.15000f, 0xffffffff},
	{-0.11200f, -0.20000f, 2.70000f, 0xffffffff},
	{-0.20000f, -0.11200f, 2.70000f, 0xffffffff},
	{-0.20000f,  0.00000f, 2.70000f, 0xffffffff},
	{ 0.00000f,  0.00200f, 3.15000f, 0xffffffff},
	{-0.80000f,  0.45000f, 3.15000f, 0xffffffff},
	{-0.45000f,  0.80000f, 3.15000f, 0xffffffff},
	{ 0.00000f,  0.80000f, 3.15000f, 0xffffffff},
	{-0.20000f,  0.11200f, 2.70000f, 0xffffffff},
	{-0.11200f,  0.20000f, 2.70000f, 0xffffffff},
	{ 0.00000f,  0.20000f, 2.70000f, 0xffffffff},
	{ 0.45000f,  0.80000f, 3.15000f, 0xffffffff},
	{ 0.80000f,  0.45000f, 3.15000f, 0xffffffff},
	{ 0.11200f,  0.20000f, 2.70000f, 0xffffffff},
	{ 0.20000f,  0.11200f, 2.70000f, 0xffffffff},
	{ 0.40000f,  0.00000f, 2.55000f, 0xffffffff},
	{ 0.40000f, -0.22400f, 2.55000f, 0xffffffff},
	{ 0.22400f, -0.40000f, 2.55000f, 0xffffffff},
	{ 0.00000f, -0.40000f, 2.55000f, 0xffffffff},
	{ 1.30000f,  0.00000f, 2.55000f, 0xffffffff},
	{ 1.30000f, -0.72800f, 2.55000f, 0xffffffff},
	{ 0.72800f, -1.30000f, 2.55000f, 0xffffffff},
	{ 0.00000f, -1.30000f, 2.55000f, 0xffffffff},
	{ 1.30000f,  0.00000f, 2.40000f, 0xffffffff},
	{ 1.30000f, -0.72800f, 2.40000f, 0xffffffff},
	{ 0.72800f, -1.30000f, 2.40000f, 0xffffffff},
	{ 0.00000f, -1.30000f, 2.40000f, 0xffffffff},
	{-0.22400f, -0.40000f, 2.55000f, 0xffffffff},
	{-0.40000f, -0.22400f, 2.55000f, 0xffffffff},
	{-0.40000f,  0.00000f, 2.55000f, 0xffffffff},
	{-0.72800f, -1.30000f, 2.55000f, 0xffffffff},
	{-1.30000f, -0.72800f, 2.55000f, 0xffffffff},
	{-1.30000f,  0.00000f, 2.55000f, 0xffffffff},
	{-0.72800f, -1.30000f, 2.40000f, 0xffffffff},
	{-1.30000f, -0.72800f, 2.40000f, 0xffffffff},
	{-1.30000f,  0.00000f, 2.40000f, 0xffffffff},
	{-0.40000f,  0.22400f, 2.55000f, 0xffffffff},
	{-0.22400f,  0.40000f, 2.55000f, 0xffffffff},
	{ 0.00000f,  0.40000f, 2.55000f, 0xffffffff},
	{-1.30000f,  0.72800f, 2.55000f, 0xffffffff},
	{-0.72800f,  1.30000f, 2.55000f, 0xffffffff},
	{ 0.00000f,  1.30000f, 2.55000f, 0xffffffff},
	{-1.30000f,  0.72800f, 2.40000f, 0xffffffff},
	{-0.72800f,  1.30000f, 2.40000f, 0xffffffff},
	{ 0.00000f,  1.30000f, 2.40000f, 0xffffffff},
	{ 0.22400f,  0.40000f, 2.55000f, 0xffffffff},
	{ 0.40000f,  0.22400f, 2.55000f, 0xffffffff},
	{ 0.72800f,  1.30000f, 2.55000f, 0xffffffff},
	{ 1.30000f,  0.72800f, 2.55000f, 0xffffffff},
	{ 0.72800f,  1.30000f, 2.40000f, 0xffffffff},
	{ 1.30000f,  0.72800f, 2.40000f, 0xffffffff},
	{ 0.00000f,  0.00000f, 0.00000f, 0xffffffff},
	{ 1.50000f,  0.00000f, 0.15000f, 0xffffffff},
	{ 1.50000f,  0.84000f, 0.15000f, 0xffffffff},
	{ 0.84000f,  1.50000f, 0.15000f, 0xffffffff},
	{ 0.00000f,  1.50000f, 0.15000f, 0xffffffff},
	{ 1.50000f,  0.00000f, 0.07500f, 0xffffffff},
	{ 1.50000f,  0.84000f, 0.07500f, 0xffffffff},
	{ 0.84000f,  1.50000f, 0.07500f, 0xffffffff},
	{ 0.00000f,  1.50000f, 0.07500f, 0xffffffff},
	{ 1.42500f,  0.00000f, 0.00000f, 0xffffffff},
	{ 1.42500f,  0.79800f, 0.00000f, 0xffffffff},
	{ 0.79800f,  1.42500f, 0.00000f, 0xffffffff},
	{ 0.00000f,  1.42500f, 0.00000f, 0xffffffff},
	{-0.84000f,  1.50000f, 0.15000f, 0xffffffff},
	{-1.50000f,  0.84000f, 0.15000f, 0xffffffff},
	{-1.50000f,  0.00000f, 0.15000f, 0xffffffff},
	{-0.84000f,  1.50000f, 0.07500f, 0xffffffff},
	{-1.50000f,  0.84000f, 0.07500f, 0xffffffff},
	{-1.50000f,  0.00000f, 0.07500f, 0xffffffff},
	{-0.79800f,  1.42500f, 0.00000f, 0xffffffff},
	{-1.42500f,  0.79800f, 0.00000f, 0xffffffff},
	{-1.42500f,  0.00000f, 0.00000f, 0xffffffff},
	{-1.50000f, -0.84000f, 0.15000f, 0xffffffff},
	{-0.84000f, -1.50000f, 0.15000f, 0xffffffff},
	{ 0.00000f, -1.50000f, 0.15000f, 0xffffffff},
	{-1.50000f, -0.84000f, 0.07500f, 0xffffffff},
	{-0.84000f, -1.50000f, 0.07500f, 0xffffffff},
	{ 0.00000f, -1.50000f, 0.07500f, 0xffffffff},
	{-1.42500f, -0.79800f, 0.00000f, 0xffffffff},
	{-0.79800f, -1.42500f, 0.00000f, 0xffffffff},
	{ 0.00000f, -1.42500f, 0.00000f, 0xffffffff},
	{ 0.84000f, -1.50000f, 0.15000f, 0xffffffff},
	{ 1.50000f, -0.84000f, 0.15000f, 0xffffffff},
	{ 0.84000f, -1.50000f, 0.07500f, 0xffffffff},
	{ 1.50000f, -0.84000f, 0.07500f, 0xffffffff},
	{ 0.79800f, -1.42500f, 0.00000f, 0xffffffff},
	{ 1.42500f, -0.79800f, 0.00000f, 0xffffffff},
};

static const uint16_t cubeTriList[] =
{
	 1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,
	 4,  17,  18,  19,   8,  20,  21,  22,  12,  23,  24,  25,  16,  26,  27,  28,
	19,  29,  30,  31,  22,  32,  33,  34,  25,  35,  36,  37,  28,  38,  39,  40,
	31,  41,  42,   1,  34,  43,  44,   5,  37,  45,  46,   9,  40,  47,  48,  13,
	13,  14,  15,  16,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,
	16,  26,  27,  28,  52,  61,  62,  63,  56,  64,  65,  66,  60,  67,  68,  69,
	28,  38,  39,  40,  63,  70,  71,  72,  66,  73,  74,  75,  69,  76,  77,  78,
	40,  47,  48,  13,  72,  79,  80,  49,  75,  81,  82,  53,  78,  83,  84,  57,
	57,  58,  59,  60,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,
	60,  67,  68,  69,  88,  97,  98,  99,  92, 100, 101, 102,  96, 103, 104, 105,
	69,  76,  77,  78,  99, 106, 107, 108, 102, 109, 110, 111, 105, 112, 113, 114,
	78,  83,  84,  57, 108, 115, 116,  85, 111, 117, 118,  89, 114, 119, 120,  93,
	121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136,
	124, 137, 138, 121, 128, 139, 140, 125, 132, 141, 142, 129, 136, 143, 144, 133,
	133, 134, 135, 136, 145, 146, 147, 148, 149, 150, 151, 152,  69, 153, 154, 155,
	136, 143, 144, 133, 148, 156, 157, 145, 152, 158, 159, 149, 155, 160, 161,  69,
	162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177,
	165, 178, 179, 162, 169, 180, 181, 166, 173, 182, 183, 170, 177, 184, 185, 174,
	174, 175, 176, 177, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197,
	177, 184, 185, 174, 189, 198, 199, 186, 193, 200, 201, 190, 197, 202, 203, 194,
	270, 270, 270, 270, 279, 280, 281, 282, 275, 276, 277, 278,  93, 120, 119, 114,
	270, 270, 270, 270, 282, 289, 290, 291, 278, 286, 287, 288, 114, 113, 112, 105,
	270, 270, 270, 270, 291, 298, 299, 300, 288, 295, 296, 297, 105, 104, 103,  96,
	270, 270, 270, 270, 300, 305, 306, 279, 297, 303, 304, 275,  96,  95,  94,  93
};
*/

static renderer::PosColorVertex cubeVertices[] =
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
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

void TestLayer::update(f32 deltaTime) {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }

	if(Input::isKeyPressed(D)) {
		position.x += 10.0f * deltaTime;
	}

	if(Input::isKeyPressed(A)) {
		position.x -= 10.0f * deltaTime;
		Application::get().removeLayer("name");
	}

	if(Input::isKeyPressed(W)) {
		position.z += 10.0f * deltaTime;
	}

	if(Input::isKeyPressed(S)) {
		position.z -= 10.0f * deltaTime;
	}

	const bx::Vec3 at = position;
	const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};

	float view[16];
	bx::mtxLookAt(view, eye, at);
	bx::mtxTranslate(view, -position.x, -position.y+sin(rotation), -position.z+5.0f);
	float proj[16];
	bx::mtxProj(proj, 60.0f, (float)Application::get().getWindow().width/(float)Application::get().getWindow().height, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);
	float mtx[16];
	bx::mtxRotateXYZ(mtx, rotation, rotation, rotation);
	bgfx::setTransform(mtx);

	renderer::renderModel(model);

	rotation += 1.0f * deltaTime;
}

void TestLayer::start() {
	//model = renderer::loadModel(cubeVertices, sizeof(cubeVertices), cubeTriList, sizeof(cubeTriList));
	model = renderer::loadModel("../overture/res/viking_room.obj");

	vsh = renderer::loadShader("../overture/res/shaders/", "vs_cubes.bin");
	fsh = renderer::loadShader("../overture/res/shaders/", "fs_cubes.bin");

	model.program = bgfx::createProgram(vsh, fsh, true);

    DEBUG("it works");
}

void TestLayer::end() {
		renderer::destroy(model);
}
