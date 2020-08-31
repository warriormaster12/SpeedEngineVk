#pragma once 

#include "VkIncludes.h"

#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>
#include <StandAlone/DirStackFileIncluder.h>

namespace VkRenderer
{
   class VkShader
    {
    public: 
        VkShader();
        
        VkShaderModule createShaderModule(const std::vector<unsigned int>& code, VkDevice& device);

        std::string GetSuffix(const std::string& name);
        EShLanguage GetShaderStage(const std::string& stage);
        

        const std::vector<unsigned int> CompileGLSL(const std::string& filename, const std::string& compiled_shader);
        std::string GetFilePath(const std::string& str);
    private:
        bool glslangInitialized = false;
        TBuiltInResource DefaultTBuiltInResource {};
       
    };
}

