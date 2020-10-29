#pragma once 

#include "../VulkanIncludes.h"

#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>
#include <StandAlone/DirStackFileIncluder.h>

namespace Renderer
{
   class VulkanShaderManager
    {
    public: 
        VulkanShaderManager();
        
        VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice& device);

        std::string GetSuffix(const std::string& name);
        EShLanguage GetShaderStage(const std::string& stage);

        static std::vector<char> readFile(const std::string& filename);
        

        const std::vector<unsigned int> CompileGLSL(const std::string& filename);
        std::string GetFilePath(const std::string& str);
    private:
        bool glslangInitialized = false;
        TBuiltInResource DefaultTBuiltInResource {};
        
       
    };
}

