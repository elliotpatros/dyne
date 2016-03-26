#version 330 core

struct PointLight {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float linear;
    float quadratic;
    float shininess;
};

in vec3 fsPositionition;
in vec3 fsNormal;
in vec3 fsColor;

out vec4 color;

uniform vec3 viewPos;
uniform PointLight light;

void main()
{
    // properties
    vec3 lightDist = vec3(light.position - fsPosition);
    vec3 viewDir = normalize(viewPos - fsPosition);
    vec3 normal = normalize(fsNormal);
    vec3 lightDir = normalize(lightDist);
    
    // attenuation
    float dist = length(lightDist);
    float atten = 1.f / (1.f + (light.linear * dist) + (light.quadratic * (dist * dist) ));
    
    // diffuse
    float diff = max(dot(normal, lightDir), 0.f);
    
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.f), light.shininess);
    
    // combined results
    vec3 ambient = fsColor * light.ambient;
    vec3 diffuse = light.diffuse * (diff * fsColor);
    vec3 specular = light.specular * (spec * fsColor);
    vec3 lightColor = ambient + ( (diffuse + specular) * atten);
    
    color = vec4(lightColor, 1.f);
}
