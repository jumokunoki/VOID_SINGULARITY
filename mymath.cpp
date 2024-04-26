// �Ǝ��v�Z���C�u����
#include "mymath.h"


// degree��radian
float DegToRad(float deg) {
    return deg * PI / 180.0f;		// �p�x��degree����radian�ɕϊ�
}

// radian��degree
float RadToDeg(float rad) {
    return rad * 180.0f / PI;		// �p�x��radian����degree�ɕϊ�
}



// �����蔻��p�B2��box�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitBox(
    int x1, int y1, int w1, int h1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
    int x2, int y2, int w2, int h2		// �ӂ��߂�box ����(x,y), �傫��w,h
) {
    if(x1 < x2 + w2 && x2 < x1 + w1		// x�����̔���
        && y1 < y2 + h2 && y2 < y1 + h1		// y�����̔���
        )
    {
        // 2��box�͓������Ă���
        return 1;
    }

    // 2��box�͓������Ă��Ȃ�
    return 0;
}




// �����蔻��p�B2�̉~�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitCircle(
    int x1, int y1, int r1,		// �ЂƂ߂�circle ���S(x,y), ���ar
    int x2, int y2, int r2		// �ӂ��߂�circle ���S(x,y), ���ar
) {
    int w, h, r;
    w = x1 - x2;
    h = y1 - y2;
    r = r1 + r2;
    if(r * r > w * w + h * h) {
        return 1;
    }
    return 0;
}

int IsHitCircleRect(
    int cx1, int cy1, int r,          // �~�̔���
    int x2, int y2, int w, int h    // ��`�̔���
 ) {
    int x, y;
    float rad, deg;
    // 360�_�Ƃ��ē����蔻�肵����ꍇ�ɂ���ďd���Ȃ�܂���
    for(deg = 0; deg <= 360; deg += 90) {
        rad = DegToRad(deg);
        x = (cx1 + r * cos(rad));
        y = (cy1 + r * sin(rad));

        // ����N�_�̋�`�̂݁i���Ԃ��Ȃ��̂Łj
        if(x2 < x && x < x2 + w && y2 < y && y < y2 + h) {
            return 1;
        }
    }

    return 0;
}



#define TwoPI   (PI * 2.0f)
#define PIOver2 (PI / 2.0f)

// �C�[�W���O
float EasingLinear(float cnt, float start, float end, float frames) {
    return (end - start) * cnt / frames + start;
}
float EasingInQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt + start;
}
float EasingOutQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * cnt * (cnt - 2) + start;
}
float EasingInOutQuad(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if(cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt + start;
    }
    cnt--;
    return -(end - start) / 2.0 * (cnt * (cnt - 2) - 1) + start;
}
float EasingInCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt + start;
}
float EasingOutCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt + 1) + start;
}
float EasingInOutCubic(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if(cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (cnt * cnt * cnt + 2) + start;
}
float EasingInQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt + start;
}
float EasingOutQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return -(end - start) * (cnt * cnt * cnt * cnt - 1) + start;
}
float EasingInOutQuart(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if(cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return -(end - start) / 2.0 * (cnt * cnt * cnt * cnt - 2) + start;
}
float EasingInQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt * cnt + start;
}
float EasingOutQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt * cnt * cnt + 1) + start;
}
float EasingInOutQuint(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if(cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (cnt * cnt * cnt * cnt * cnt + 2) + start;
}
float EasingInSine(float cnt, float start, float end, float frames) {
    return -(end - start) * cos(cnt / frames * (PIOver2)) + end + start;
}
float EasingOutSine(float cnt, float start, float end, float frames) {
    return (end - start) * sin(cnt / frames * PIOver2) + start;
}
float EasingInOutSine(float cnt, float start, float end, float frames) {
    return -(end - start) / 2.0 * (cos(PI * cnt / frames) - 1) + start;
}
float EasingInExpo(float cnt, float start, float end, float frames) {
    return (end - start) * pow(2.0, 10 * (cnt / frames - 1)) + start;
}
float EasingOutExpo(float cnt, float start, float end, float frames) {
    return (end - start) * (-pow(2.0, -10 * cnt / frames) + 1) + start;
}
float EasingInOutExpo(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if(cnt < 1) {
        return (end - start) / 2.0 * pow(2.0, 10 * (cnt - 1)) + start;
    }
    cnt--;
    return (end - start) / 2.0 * (-pow(2.0, -10 * cnt) + 2) + start;
}
float EasingInCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * (sqrt(1 - cnt * cnt) - 1) + start;
}
float EasingOutCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * sqrt(1 - cnt * cnt) + start;
}
float EasingInOutCirc(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if(cnt < 1) {
        return -(end - start) / 2.0 * (sqrt(1 - cnt * cnt) - 1) + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (sqrt(1 - cnt * cnt) + 1) + start;
}

// �͈͓���Ԃ�
float Clamp(float min_n, float max_n, float n) {
    if(n <= min_n) { return min_n; }
    if(n >= max_n) { return max_n; }
    return n;
}