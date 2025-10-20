#version 460 core
out vec4 FragColor;

in vec3 ourColor;
uniform float time;

void main() {
    // ��������� ���� � ������� ������ � �������� �� �������
    float r = (sin(time) + 1.0) * 0.5;           // �� 0 �� 1
    float g = (cos(time * 1.5) + 1.0) * 0.5;     // �� 0 �� 1
    float b = (sin(time * 2.0 + 1.57) + 1.0) * 0.5; // �� 0 �� 1
    
    // ����������� ������������� ���� � �������� ������ �������
    vec3 animatedColor = ourColor * vec3(r, g, b);
    
    FragColor = vec4(animatedColor, 1.0);
}