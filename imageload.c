#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

// 윈도우 크기 설정
#define WINDOW_WIDTH 1200   // 두 이미지를 나란히 출력할 수 있도록 창 크기 조정
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 실패: %s\n", SDL_GetError());
        return 1;
    }

    // SDL_image 초기화 (JPG 및 PNG 지원)
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        printf("SDL_image 초기화 실패: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // 윈도우 생성
    SDL_Window* window = SDL_CreateWindow("이미지 출력 예제",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("윈도우 생성 실패: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("렌더러 생성 실패: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 이미지 파일 경로 설정 (JPG 및 PNG 파일)
    const char* imageFilePath1 = "jcshim.jpg";  // JPG 이미지
    const char* imageFilePath2 = "jcshim.png";  // PNG 이미지

    // 첫 번째 이미지 (JPG) 로드
    SDL_Surface* imageSurface1 = IMG_Load(imageFilePath1);
    if (!imageSurface1) {
        printf("JPG 이미지 로드 실패: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 두 번째 이미지 (PNG) 로드
    SDL_Surface* imageSurface2 = IMG_Load(imageFilePath2);
    if (!imageSurface2) {
        printf("PNG 이미지 로드 실패: %s\n", IMG_GetError());
        SDL_FreeSurface(imageSurface1);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 서피스를 텍스처로 변환
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, imageSurface1);
    SDL_FreeSurface(imageSurface1);  // 서피스는 더 이상 필요 없음
    if (!texture1) {
        printf("텍스처 1 생성 실패: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, imageSurface2);
    SDL_FreeSurface(imageSurface2);  // 서피스는 더 이상 필요 없음
    if (!texture2) {
        printf("텍스처 2 생성 실패: %s\n", SDL_GetError());
        SDL_DestroyTexture(texture1);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 화면에 두 이미지 출력
    SDL_RenderClear(renderer);

    // 첫 번째 이미지 (JPG)
    SDL_Rect destRect1 = { 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT };  // 창의 왼쪽 절반
    SDL_RenderCopy(renderer, texture1, NULL, &destRect1);

    // 두 번째 이미지 (PNG)
    SDL_Rect destRect2 = { WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT };  // 창의 오른쪽 절반
    SDL_RenderCopy(renderer, texture2, NULL, &destRect2);

    // 화면에 이미지를 출력
    SDL_RenderPresent(renderer);

    // 5초 동안 대기 (이미지를 5초간 표시)
    SDL_Delay(5000);

    // 자원 정리
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
