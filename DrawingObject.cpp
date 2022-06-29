#include "DrawingObject.h"

DrawingObject::DrawingObject()
{
	uint16_t indices[] =
	{
		0,1,2,	//�����O�p�`
		//1,2,3,	//�E��O�p�`
	};


	//���_�f�[�^
	XMFLOAT3 vertices[] = {
	{ -0.5f, -0.5f, 0.0f }, // ����
	{ -0.5f, +0.5f, 0.0f }, // ����
	//{ +0.5f, -0.5f, 0.0f }, // �E��
	//{ +0.5f, +0.5f, 0.0f }	//�E��
	};
	

	

}

void DrawingObject::init(ID3D12Device* device) {
	//DXGI�t�@�N�g���[�̐���
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	//�A�_�v�^�̗񋓗p
	std::vector<IDXGIAdapter4*>adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������

	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));
	

	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;	//�C���f�b�N�X��񂪓��镪�̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�C���f�b�N�X�o�b�t�@�̐���
	ID3D12Resource* indexBuff = nullptr;
	result = device->CreateCommittedResource(
		&heapProp,	//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));

	result = indexBuff->Map(0, nullptr, (void**)&indexMap);

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	//�Ȃ��������
	vertBuff->Unmap(0, nullptr);

	//GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();

	vbView.SizeInBytes = sizeVB;
	//���_�o�b�t�@�̃T�C�Y
	vbView.StrideInBytes = sizeof(XMFLOAT3);//

	//�}�b�s���O����
	indexBuff->Unmap(0, nullptr);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
	//3-4 20p�܂�

}



void DrawingObject::Update()
{

	
	//�S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++) {
		vertMap[i] = vertices[i];
	}
}




void DrawingObject::Draw(ID3D12GraphicsCommandList* commandList, ID3D12Resource* constBuffMaterial, D3D12_INDEX_BUFFER_VIEW ibView, ID3D12PipelineState* pipelineState, ID3D12RootSignature* rootSignature)
{

	//�p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	commandList->SetPipelineState(pipelineState);
	commandList->SetGraphicsRootSignature(rootSignature);



	//�v���~�e�B�u�`��̐ݒ�R�}���h
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//�O�p�`���X�g

	//���_�o�b�t�@�r���[�̐ݒ�R�}���h
	commandList->IASetVertexBuffers(0, 1, &vbView);

	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	commandList->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h 3-4
	commandList->IASetIndexBuffer(&ibView);
	//�`��R�}���h
	commandList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);	//�S�Ă̒��_���g���ĕ`��



	



}
