#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> data;     //비어있는 상태 새로 채워가야함
    data.reserve(n);

    // TODO: n개의 가변 길이 정수 배열을 입력받아 data에 저장하세요.

    for (int i = 0; i < n; i++)
    {
        data.push_back(std::vector<int>(m)); // 각 행에 m개의 열을 미리 할당(뒤에서 푸쉬하는게 아니라 앞에서 부터 하나씩 바꿔가야함)
        int vec_num;
        std::cin >> vec_num; // 각 행의 실제 길이 입력
        for (int j = 0; j < vec_num; j++)
        {
            int num;
            std::cin >> num; // 입력된 길이만큼 데이터 저장
            data[i].push_back(num);

            // std::cin >> data[i][j]; // 입력된 길이만큼 데이터 저장
        }
    }
    




    for (int i = 0; i < n; i++)
    {
        int l=0;
        std:: cin >> l;

        std:: vector<int> sub;
        for (int j = 0; j < l; j++)
        {
            int k=0;
            std::cin >> k;
            sub.push_back(k);
        }
        data.push_back(sub);
    }
    

    // TODO: m개의 질문 (i, j)을 입력받아 data[i][j]를 한 줄에 하나씩 출력하세요.
    int q1, q2;
    for (int i = 0; i < m; i++)
    {
        std::cin >> q1 >> q2;
        std::cout << data[q1][q2] << " ";
    }
    


    int arr[m];
    for (int i = 0; i < m; i++)
    {
        int r =0, c=0;
        std::cin>>r>>c;
        arr[i] = data[r][c];
    }
    for (int i = 0; i<m; i++) {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
    
    return 0;
}
