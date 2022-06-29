#pragma once
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
#include"global.h"

using namespace DirectX;
using namespace std;

class DrawingObject
{
private:


	HRESULT result;

	uint16_t indices[3];//インデックス


	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;

	//ここに特定の名前を持つアダプターオブジェクトが入る
	IDXGIAdapter4* tmpAdapter = nullptr;


	//頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));

	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{}; // ヒープ設定
	
	//頂点バッファの生成
	ID3D12Resource* vertBuff = nullptr;
	


	//GPU乗のバッファに対応した仮想メモリ(メインメモリ上)を取得
	XMFLOAT3* vertMap = nullptr;
	

	//頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	

	//インデックスデータ全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));

	//インデックスバッファをマッピング
	uint16_t* indexMap = nullptr;


public:
	DrawingObject();

	


	
	//頂点データ
	struct XMFLOAT3 vertices[2];

	void init(ID3D12Device* device);
	
	void Update();

	void Draw(ID3D12GraphicsCommandList* commandList, ID3D12Resource* constBuffMaterial, D3D12_INDEX_BUFFER_VIEW ibView, ID3D12PipelineState* pipelineState, ID3D12RootSignature* rootSignature);


};

