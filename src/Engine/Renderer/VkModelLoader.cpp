#include "Engine/Renderer/VkModelLoader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "Engine/Renderer/tinyobjloader/tiny_obj_loader.h"


namespace std {
    template<> struct hash<VkRenderer::Vertex> {
        size_t operator()(VkRenderer::Vertex const& vertex) const {
            size_t h1 = hash<glm::vec3>()(vertex.pos);
            size_t h2 = hash<glm::vec3>()(vertex.color);
            size_t h3 = hash<glm::vec2>()(vertex.texCoord);
            size_t h4 = hash<glm::vec3>()(vertex.normal);

            return((((h1 ^ (h2 << 1)) >> 1) ^ h3) << 1) ^ h4;
        }
    };
}

namespace VkRenderer
{
    
    

    
    void ModelLoader::loadModel()
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
            throw std::runtime_error(warn + err);
        }
        
        std::unordered_map<Vertex, uint32_t> uniqueVertices{};

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};
                
                vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };
                
               
                vertex.normal = 
                {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
                
                
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };
                
                
                vertex.color = {1.0f, 1.0f, 1.0f};
                

                 if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertexBuffer_ref->vertices.size());
                    vertexBuffer_ref->vertices.push_back(vertex);
                }
                

                
                indexBuffer_ref->indices.push_back(uniqueVertices[vertex]);

            }
        }

    }
}