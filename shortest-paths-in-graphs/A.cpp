#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::string start;
    std::cin >> start;
    std::pair<int, int> start_pos = std::make_pair(start[0] - 'a', start[1] - '1');

    std::string finish;
    std::cin >> finish;
    std::pair<int, int> finish_pos = std::make_pair(finish[0] - 'a', finish[1] - '1');

    std::vector<std::vector<std::pair<int, std::pair<int, int>>>> chessboard (8, std::vector<std::pair<int, std::pair<int, int>>> (8, std::make_pair(-1, std::make_pair(-1, -1))));

    chessboard[start_pos.first][start_pos.second].first = 0;

    std::queue<std::pair<int, int>> cell_queue;
    cell_queue.push(start_pos);

    while (chessboard[finish_pos.first][finish_pos.second].first == -1) {
        std::pair<int, int> current_cell = cell_queue.front();

        if (current_cell.first + 1 < 8 && current_cell.second + 2 < 8 && chessboard[current_cell.first + 1][current_cell.second + 2].first == -1) {
            chessboard[current_cell.first + 1][current_cell.second + 2].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first + 1][current_cell.second + 2].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first + 1, current_cell.second + 2));
        }
        if (current_cell.first + 2 < 8 && current_cell.second + 1 < 8 && chessboard[current_cell.first + 2][current_cell.second + 1].first == -1) {
            chessboard[current_cell.first + 2][current_cell.second + 1].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first + 2][current_cell.second + 1].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first + 2, current_cell.second + 1));
        }
        if (current_cell.first + 1 < 8 && current_cell.second - 2 > -1 && chessboard[current_cell.first + 1][current_cell.second - 2].first == -1) {
            chessboard[current_cell.first + 1][current_cell.second - 2].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first + 1][current_cell.second - 2].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first + 1, current_cell.second - 2));
        }
        if (current_cell.first + 2 < 8 && current_cell.second - 1 > -1 && chessboard[current_cell.first + 2][current_cell.second - 1].first == -1) {
            chessboard[current_cell.first + 2][current_cell.second - 1].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first + 2][current_cell.second - 1].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first + 2, current_cell.second - 1));
        }
        if (current_cell.first - 1 > -1 && current_cell.second + 2 < 8 && chessboard[current_cell.first - 1][current_cell.second + 2].first == -1) {
            chessboard[current_cell.first - 1][current_cell.second + 2].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first - 1][current_cell.second + 2].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first - 1, current_cell.second + 2));
        }
        if (current_cell.first - 2 > -1 && current_cell.second + 1 < 8 && chessboard[current_cell.first - 2][current_cell.second + 1].first == -1) {
            chessboard[current_cell.first - 2][current_cell.second + 1].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first - 2][current_cell.second + 1].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first - 2, current_cell.second + 1));
        }
        if (current_cell.first - 2 > -1 && current_cell.second - 1 > -1 && chessboard[current_cell.first - 2][current_cell.second - 1].first == -1) {
            chessboard[current_cell.first - 2][current_cell.second - 1].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first - 2][current_cell.second - 1].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first - 2, current_cell.second - 1));
        }
        if (current_cell.first - 1 > -1 && current_cell.second - 2 > -1 && chessboard[current_cell.first - 1][current_cell.second - 2].first == -1) {
            chessboard[current_cell.first - 1][current_cell.second - 2].first = chessboard[current_cell.first][current_cell.second].first + 1;
            chessboard[current_cell.first - 1][current_cell.second - 2].second = current_cell;
            cell_queue.push(std::make_pair(current_cell.first - 1, current_cell.second - 2));
        }

        cell_queue.pop();
    }

    std::vector<std::string> ans;

    while (chessboard[finish_pos.first][finish_pos.second].second != std::make_pair(-1, -1)){
        std::string current_cell;
        current_cell.push_back(finish_pos.first + 'a');
        current_cell.push_back(finish_pos.second + '1');

        ans.push_back(current_cell);

        finish_pos = chessboard[finish_pos.first][finish_pos.second].second;
    }
    ans.push_back(start);

    for (int i = ans.size() - 1; i >= 0; --i) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}
