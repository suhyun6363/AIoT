#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// 전역 변수로 거리 선언
unsigned int distance = 0;

// 뮤텍스와 조건 변수
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// 초음파 감지 및 거리 업데이트 스레드
void *distanceUpdateThread(void *arg) {
    while (1) {
        // 여기에 실제 초음파 감지 및 거리 업데이트 로직을 추가

        // 예시: 1에서 100 사이의 랜덤한 값을 distance에 할당
        pthread_mutex_lock(&mutex);
        distance = rand() % 100 + 1;
        pthread_mutex_unlock(&mutex);

        usleep(300000);  // 0.3초 대기
    }
    return NULL;
}

// Buzzer 제어 스레드
void *buzzerControlThread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        // 거리가 가까워질수록 빨라지는 로직 추가
        if (distance < 30) {
            // Buzzer를 더 빠르게 울리는 로직 추가
            printf("Buzzer: Beep! Beep!\n");
        }
        pthread_mutex_unlock(&mutex);

        usleep(200000);  // 0.2초 대기
    }
    return NULL;
}

// Serial LCD에 거리 출력 스레드
void *lcdDisplayThread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        // Serial LCD에 거리 출력 로직 추가
        printf("LCD Display: Distance = %u cm\n", distance);
        pthread_mutex_unlock(&mutex);

        usleep(400000);  // 0.4초 대기
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // 스레드 생성
    pthread_create(&thread1, NULL, distanceUpdateThread, NULL);
    pthread_create(&thread2, NULL, buzzerControlThread, NULL);
    pthread_create(&thread3, NULL, lcdDisplayThread, NULL);

    // 메인 스레드 대기
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
