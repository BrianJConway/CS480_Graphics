#include <iostream>
#include "texture.h"


Texture::Texture()
   {

   }
   
Texture::Texture( GLenum textureTarget, const string& fileName )
   {
    m_textureTarget = textureTarget;
    m_fileName = "models/" + fileName;
   }


bool Texture::Load()
   {
    try 
       {
        m_image.read(m_fileName);
        m_image.write(&m_blob, "RGBA");
       }
    catch (Magick::Error& Error) 
       {
        cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
       }

    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    glTexImage2D(m_textureTarget, 0, GL_RGBA, m_image.columns(), m_image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    glBindTexture(m_textureTarget, 0);
    
    return true;
   }

void Texture::Bind(GLenum TextureUnit)
   {
    glActiveTexture(TextureUnit);
    glBindTexture( m_textureTarget, m_textureObj );
   }
