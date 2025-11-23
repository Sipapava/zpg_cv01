#include "modelManager.h"
#include <algorithm>

#include "tree.h"
#include "skycube.h"
#include "bushes.h"
#include "sphere.h"

ModelManager::~ModelManager()
{
	for (Model* m : models) {
		delete m;
	}
	models.clear();
}

Model* ModelManager::CreateModel(const Vertex* vertices, size_t count, const std::string& type, const std::string& name)
{
	Model* newModel = new Model(vertices, count, type, name);
	models.push_back(newModel);
	return newModel;
}

Model* ModelManager::GetModelByName(const std::string& name) const
{
	for (Model* m : models) {
		if (m->getName() == name) {
			return m;
		}
	}
	return nullptr;
}


void ModelManager::createModelsForScenes() {

    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize, false, true);

    std::vector<std::string> faces = {
    "skybox/posx.jpg",
    "skybox/negx.jpg",
    "skybox/posy.jpg",
    "skybox/negy.jpg",
    "skybox/posz.jpg",
    "skybox/negz.jpg"
    };

    const int cubeSize = sizeof(skycube) / sizeof(skycube[0]);
    std::vector<Vertex> sunss = FromFloat(skycube, cubeSize, false, false);
    this->CreateModel(sunss.data(), sunss.size(), "triangles", "skyCube");


    this->CreateModel(sphereV.data(), sphereV.size(), "triangles", "sphere");

    std::vector<Vertex> form = this->LoadModelFromObjectFile("models/formula1.obj");
    this->CreateModel(form.data(), form.size(), "triangles", "formule");

    const Vertex planeVertices[] = {
        // pozice                   normal                     uv
        {{-2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {100.0f, 0.0f}},
        {{ 2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {100.0f, 100.0f}},

        {{ 2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {100.0f, 100.0f}},
        {{-2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 100.0f}},
        {{-2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}}
    };


    const int treeSize = sizeof(tree) / sizeof(tree[0]);
    std::vector<Vertex> treeV = FromFloat(tree, treeSize, false, true);






    const int bushSize = sizeof(bushes) / sizeof(bushes[0]);

    std::vector<Vertex> bushV = FromFloat(bushes, bushSize, false, true);




    this->CreateModel(treeV.data(), treeV.size(), "triangles", "tree");


    this->CreateModel(bushV.data(), bushV.size(), "triangles", "bush");

    std::vector<Vertex> skydome = this->LoadModelFromObjectFile("models/skydome.obj");
    this->CreateModel(skydome.data(), skydome.size(), "triangles", "skyDom");

    this->CreateModel(planeVertices, sizeof(planeVertices) / sizeof(Vertex), "triangles", "plane");

    std::vector<Vertex> shrek = this->LoadModelFromObjectFile("models/shrek.obj");
    this->CreateModel(shrek.data(), shrek.size(), "triangles", "shrek");

    std::vector<Vertex> fiona = this->LoadModelFromObjectFile("models/fiona.obj");
    this->CreateModel(fiona.data(), fiona.size(), "triangles", "fiona");


    std::vector<Vertex> cat = this->LoadModelFromObjectFile("models/fatcat.obj");
    this->CreateModel(cat.data(), cat.size(), "triangles", "cat");

    std::vector<Vertex> spino = this->LoadModelFromObjectFile("models/spinosaurus.obj");
    this->CreateModel(spino.data(), spino.size(), "triangles", "spinosaurus");

    std::vector<Vertex> planet = this->LoadModelFromObjectFile("models/planet.obj");
    this->CreateModel(planet.data(), planet.size(), "triangles", "planet");

}


std::vector<Vertex> ModelManager::LoadModelFromObjectFile(const char* path) {
    Assimp::Importer importer;
    std::vector<Vertex> vertices;

    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate
    );

    if (!scene || !scene->HasMeshes()) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return vertices;
    }

    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[m];

        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace& face = mesh->mFaces[f];

            for (unsigned int i = 0; i < face.mNumIndices; ++i) {
                unsigned int idx = face.mIndices[i];
                Vertex v;


                v.pos = glm::vec4(
                    mesh->mVertices[idx].x,
                    mesh->mVertices[idx].y,
                    mesh->mVertices[idx].z,
                    1.0f
                );


                if (mesh->HasNormals()) {
                    v.normal = glm::vec4(
                        mesh->mNormals[idx].x,
                        mesh->mNormals[idx].y,
                        mesh->mNormals[idx].z,
                        1.0f
                    );
                }
                else {
                    v.normal = glm::vec4(0, 0, 0, 0);
                }


                if (mesh->HasTextureCoords(0)) {
                    aiVector3D tex = mesh->mTextureCoords[0][idx];
                    v.texture = glm::vec2(tex.x, tex.y);
                }
                else {
                    v.texture = glm::vec2(0.0f, 0.0f);
                }

                vertices.push_back(v);
            }
        }
    }

    return vertices;
}

std::vector<Vertex> ModelManager::FromFloat(const float* data, size_t size, bool hasTexture, bool hasNormal) {
    std::vector<Vertex> vertices;

    // 3 (pos) + 3 (normal) + 2 (tex)
    size_t stride = 3 + (hasNormal ? 3 : 0) + (hasTexture ? 2 : 0);

    if (size % stride != 0) {
        std::cerr << " FromFloat: Data size (" << size
            << ") is not a multiple of stride (" << stride << ")!\n";
    }

    for (size_t i = 0; i < size; i += stride) {
        Vertex v;

        v.pos = glm::vec4(data[i], data[i + 1], data[i + 2], 1.0f);
        size_t offset = 3;

        if (hasNormal) {
            v.normal = glm::vec4(data[i + offset], data[i + offset + 1], data[i + offset + 2], 1.0f);
            offset += 3;
        }
        else {
            v.normal = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        }

        if (hasTexture) {
            v.texture = glm::vec2(data[i + offset], data[i + offset + 1]);
            offset += 2;
        }
        else {
            v.texture = glm::vec2(1.0f);
        }

        vertices.push_back(v);
    }

    return vertices;
}