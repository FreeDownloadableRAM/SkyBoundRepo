#pragma once
#include "Utilities/MeshFactory.h"
#include "Gameplay/Scene.h"
#include "Graphics/Shader.h"

class MorphLoader
{
public:
	MorphLoader() {};
	static MeshBuilder<VertexPosNormTexCol> LoadFromFile(const std::string& filename, const glm::vec4& inColor = glm::vec4(1.0f));
	~MorphLoader();

	void UpdateData(int frameIndex0, int frameIndex1, float t);

	void blendTo(const std::string& fileName, float delay = 0.25f, int frame = 0);

	static void Init();
	static void Unload();



	bool isDone() 
	{ 
		return m_t == 1; 
	}


	MorphLoader& setSpeed(float speed)
	{
		m_speed = speed;
		return *this;
	}

	float getSpeed()
	{
		return m_speed;
	}

	static void beginDraw();

	void Update(float dt);

	void Draw(const glm::mat4& model);

	void SetFrames(const std::vector<std::unique_ptr<MeshBuilder<VertexPosNormTexCol>>>& frames);

	void SetFrameTime(float frameTime);
	



private:
	struct Frames {
		VertexBuffer::sptr pos;
		VertexBuffer::sptr normal;
		VertexBuffer::sptr colour = nullptr;
		VertexBuffer::sptr UVs = nullptr;
	};

	struct Anim {
		std::string fileName;
		bool mat;
		float startTime = 0;
		std::vector<float> durations = {};
		//std::vector<size_t> frameIndex = {};
		int frameIndex = 0;
		std::vector<Frames> frames = {};
		float m_frameTime = 0.2f;
		size_t start = 0;
		size_t t = 0;
		size_t texture = INT_MAX;
		VertexBuffer::sptr UVs = nullptr;
	};

	struct DrawData {
		float t;
		VertexArrayObject::sptr vao;
		glm::mat4 model;
		size_t texture = 0;
	};


	//static std::vector<DrawData> m_texQueue;
	//static std::vector<DrawData> m_matQueue;
	//static std::vector<DrawData> m_defaultQueue;

	//static std::vector<Anim> m_anim;

	static Shader::sptr m_shader;
	static Shader::sptr m_matShader;
	static Shader::sptr m_texShader;

	std::unique_ptr<Anim> m_anim;

	static std::vector<BufferAttribute> pos1Buff;
	static std::vector<BufferAttribute> pos2Buff;
	static std::vector<BufferAttribute> norm1Buff;
	static std::vector<BufferAttribute> norm2Buff;
	static std::vector<BufferAttribute> UVBuff;


	VertexArrayObject::sptr m_vao = nullptr;

	//Variables
	float m_t = 0;
	float m_speed = 1;
	float m_timer = 0;
	

	int frameIndex;

	size_t m_p0 = 0;
	size_t m_p1 = 0;
	size_t m_index = INT_MAX;
	//size_t m_indexHold = INT_MAX;
	//size_t m_p0Hold = 0;
	//size_t m_p1Hold = 0;

	//static std::vector<glm::vec3> loadedPositions;
	//static std::vector<glm::vec3> loadedNormals;
	//static std::vector<glm::vec2> loadedUVs;

	bool m_loop = false;

};

