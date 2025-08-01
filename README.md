# FDF
이 프로그램은 파일을 등각 투영 방식의 와이어프레임 모델로 보여줍니다. fdf는 프랑스어로 와이어 프레임을 의미하는 'fil de fer'의 약자입니다.
<img width="1899" height="1018" alt="t1_map" src="https://github.com/user-attachments/assets/9dac5e9b-1360-4143-84bd-6c3004af43e0" />

## 실행영상
https://github.com/user-attachments/assets/c5eddb8c-7d15-40aa-a3c3-59af00df3397


42의 minilibx 라이브러리를 이용해 3d wire-frame-model을 만들어보는 과제다. minilibx는 화면을 띄워주고 원하는 좌표에 점을 찍기, 키코드 관리 정도만 해주는 도구다. 투영, 변환 및 회전, 확대/축소는 직접 처리해 줘야한다.


## 설치

- Linux (o)
- macOS (x)
- Windows (x)

### 레포지토리 클론

```bash
git clone https://github.com/enkoding1/fdf
cd fdf
```

### 의존성 설치

```bash
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

### 실행 파일 생성

```bash
make bonus
```

### fdf 실행

```bash
./fdf_bonus test_maps/pyramide.fdf
```

## 수학

- 선형대수
- 3D 변환
- 투영
- 브래젠햄 알고리즘

## 프로그래밍

- C
- X11
- minilibx

## 투영

3D의 좌표계는 x, y, z를 사용한다. 하지만 pixel에 표현 해야할 수 있는 좌표는 x, y좌표 뿐이다. 3D계산을 토대로 2D좌표계에 적용시키는 것을 투영한다고 한다. 이 과제에서 기본적으로 실행됐을 땐 3D모델이 등축투영을 한 상태로 화면에 표시되어야 한다.

## 회전 행렬

![rotation_matrix](https://github.com/user-attachments/assets/65f3a909-9cfa-422a-adb8-5cc414231868)
<br>
화면에 찍히게 되는 픽섹들이 렌더링 되기 전에 좌표별 회전행렬을 계산한 후 위치를 렌더링시켜주면 입체적으로 회전하는 것 처럼 보이게된다. 
x, y, z를 회전한 위 식을 각각 코드로 풀어서 아래와 같은 함수로 추상화 했다.

### X축 회전

```c
void	rotation_x(t_pos *pos, double theta)
{
	double	radian;
	int		temp_y;
	int		temp_z;

	radian = theta * M_PI / 180;
	temp_y = pos->y;
	temp_z = pos->z;
	pos->x = pos->x;
	pos->y = (temp_y * cos(radian) - temp_z * sin(radian));
	pos->z = (temp_y * sin(radian) + temp_z * cos(radian));
}
```

### Y축 회전

```c
void	rotation_y(t_pos *pos, double theta)
{
	double	radian;
	int		temp_x;
	int		temp_z;

	radian = theta * M_PI / 180;
	temp_x = pos->x;
	temp_z = pos->z;
	pos->x = (temp_x * cos(radian) + temp_z * sin(radian));
	pos->y = pos->y;
	pos->z = -temp_x * sin(radian) + temp_z * cos(radian);
}
```

### Z축 회전

```c
void	rotation_z(t_pos *pos, double theta)
{
	double	radian;
	int		temp_x;
	int		temp_y;

	radian = theta * M_PI / 180;
	temp_x = pos->x;
	temp_y = pos->y;
	pos->x = (temp_x * cos(radian) - temp_y * sin(radian));
	pos->y = (temp_x * sin(radian) + temp_y * cos(radian));
	pos->z = pos->z;
}
```

### 등축투영

```c
void	set_isometric_projection(t_pos *pos)
{
	double	vertical_axis;
	double	horizontal_axis;

	vertical_axis = 45.0;
	horizontal_axis = 35.264;
	rotation_z(pos, vertical_axis);
	rotation_x(pos, horizontal_axis);
}
```

이 과제를 통해 3D 그래픽스에서 회전 원리, 브레젠헴 선긋기 알고리즘, 변환후 렌더링 시점, 투영을 적용해보며 원리를 파악할 수 있었다.
