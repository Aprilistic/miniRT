# miniRT
<img width="1392" alt="Screen Shot 2023-02-27 at 6 50 33 PM" src="https://user-images.githubusercontent.com/70141850/236366401-55990229-0a26-4912-b26f-56c277971704.png">

We made a ray tracing renderer in C.

## How we coded?
### Ray
Everything is rendered by vector operation. Ray starts from the camera then traces the closest object and reflects from it. When a ray hits a surface, it leads to creating two new rays(diffuse reflection, and specular reflection). In default, reflection is limited to 3 times(2^3 vector calculations per pixel)

### Objects
1. Plane
2. Sphere
3. Cylinder

## How to run? (Works on macOS)
Enter the command 'make' in the cloned folder. Then executable named 'miniRT' will appear. Run it with the provided .rt file!
'./miniRT /rt/pyramid.rt'


## Keys
<kbd>↑</kbd> : Forward

<kbd>↓</kbd> : Backward

<kbd>←</kbd> : Left

<kbd>→</kbd> : Right

<kbd>PageUp</kbd> : Ascend

<kbd>PageDown</kbd> : Descend



## Screenshots
| | | |
|:-------------------------:|:-------------------------:|:-------------------------:|
| <img width="1392" alt="mirror" src="https://user-images.githubusercontent.com/70141850/236367530-b66fda37-b53e-4dff-8db7-da27b00abe09.png"> Mirror | <img width="1392" alt="rainbow" src="https://user-images.githubusercontent.com/70141850/236367676-4098b4d1-6d8f-44bb-b3c2-9ec08b83094d.png"> Rainbow  | <img width="1392" alt="snowman" src="https://user-images.githubusercontent.com/70141850/236367828-a9455284-5153-4938-85c4-8353efa55686.png"> Snowman |
| <img width="1392" alt="complex" src="https://user-images.githubusercontent.com/70141850/236367913-3dbae8dd-94e2-455e-b88b-bcf70e1f1916.png"> Complex | <img width="1392" alt="pyramid" src="https://user-images.githubusercontent.com/70141850/236368069-1ededc0c-eb8f-412b-9448-bdc0bb79cca8.png"> Pyramid | <img width="1392" alt="shadow" src="https://user-images.githubusercontent.com/70141850/236368078-1be33dca-ea9d-4eea-a897-272eca36699f.png"> Shadow |

## Reference
Ray Tracing in One Weekend

https://raytracing.github.io
