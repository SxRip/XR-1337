#pragma once
#include <exception>
#include <Windows.h>


#define VERIFY(call) if(!call) throw std::exception("error")
#define VERIFYD3D(call) if(FAILED(call)) throw std::exception("D3DError");