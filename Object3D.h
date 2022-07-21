#define DIRECTINPUT_VERSION 0x0800 //DirectInputのバージョン指定
#include<dinput.h>
#include<d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include<Windows.h>
#include <tchar.h>
#include<iostream>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <vector>
#include <string>
#include<DirectXMath.h>
#include<math.h>
#include <DirectXTex.h>
#include<wrl.h>

const float PI = 3.14f;


using namespace DirectX;
using namespace std;

using namespace Microsoft::WRL;


//定数バッファ用データ構造体
struct ConstBufferDataTransform {
	XMMATRIX mat;
};

struct Object3d {
	ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;

	XMFLOAT3 scale = { 1,1,1 };
	XMFLOAT3 rotation = { 0,0,0 };
	XMFLOAT3 position = { 0,0,0 };

	XMMATRIX matWorld{};

	Object3d* parent = nullptr;

};

void InitializeObject3d(Object3d* object, ID3D12Device* device)