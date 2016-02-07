#ifndef _VECTOR_H_
    #define _VECTOR_H_

template<typename T>
    struct Vector2 {
        T x;
        T y;

        Vector2(): x(), y() {}
        Vector2(T xarg, T yarg): x(xarg), y(yarg) {}
    };


template<typename T>
    struct Vector3 {
        T pitch;
        T roll;
        T yaw;

        Vector3(): pitch(), roll(), yaw() {}
        Vector3(T pitcharg, T rollarg, T yawarg): pitch(pitcharg), roll(rollarg), yaw(yawarg) {}
    };

#endif
