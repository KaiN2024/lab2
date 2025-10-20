#version 460 core
out vec4 FragColor;

in vec3 ourColor;
uniform float time;

void main() {
    // Анимируем цвет с помощью синуса и косинуса от времени
    float r = (sin(time) + 1.0) * 0.5;           // от 0 до 1
    float g = (cos(time * 1.5) + 1.0) * 0.5;     // от 0 до 1
    float b = (sin(time * 2.0 + 1.57) + 1.0) * 0.5; // от 0 до 1
    
    // Комбинируем анимированный цвет с исходным цветом вершины
    vec3 animatedColor = ourColor * vec3(r, g, b);
    
    FragColor = vec4(animatedColor, 1.0);
}