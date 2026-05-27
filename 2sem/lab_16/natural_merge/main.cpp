#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int distribution(string main_path, string path1, string path2) {
    ofstream f1, f2;
    ifstream mainf;
    f1.open(path1);
    f2.open(path2);
    mainf.open(main_path);

    if (!f1.is_open() || !f2.is_open() || !mainf.is_open()) {
        cout << "Error" << endl;
        return -1;
    }
    else {     
        int cur, temp;
        int series_cnt = 0;
        bool write_to_f1 = true;
        bool first = true;

        if (mainf >> cur) {
            series_cnt = 1;

            if (write_to_f1) {
                f1 << cur << ' ';
            }
            else {
                f2 << cur << ' ';
            }

            while (mainf >> temp) {
                if (temp < cur) {
                    series_cnt++;
                    write_to_f1 = !write_to_f1;
                }
                cur = temp;

                if (write_to_f1) {
                    f1 << cur << ' ';
                }
                else {
                    f2 << cur << ' ';
                }
            }
        }
        mainf.close();
        f1.close();
        f2.close();

        return series_cnt;
    }
}

int merge(string in1, string in2, string out1, string out2) {
    ifstream f1, f2;
    ofstream f3, f4;

    f1.open(in1);
    f2.open(in2);
    f3.open(out1);
    f4.open(out2);

    if (!f1.is_open() || !f2.is_open() || !f3.is_open() || !f4.is_open()) {
        cout << "Error" << endl;
        return -1;
    }
    else {
        int series_out = 0;
        bool cur_is_f3 = true;
        int val1, val2;
        bool have1 = static_cast<bool>(f1 >> val1);
        bool have2 = static_cast<bool>(f2 >> val2);
        int prev1, prev2;

        while (have1 || have2) {
            series_out++;
            ofstream * cur_out;

            if (cur_is_f3) {
                cur_out = &f3;
            }
            else {
                cur_out = &f4;
            }
            
            bool end_series1 = false;
            bool end_series2 = false;
            bool stop_series = false;

            while (!stop_series) {
                bool take_from_1 = false;

                if (!end_series1 && have1 && (end_series2 || !have2 || val1 <= val2)) {
                    take_from_1 = true;
                }
                else if (!end_series2 && have2) {
                    take_from_1 = false;
                }
                else if (end_series1 && !end_series2) {
                    take_from_1 = false;
                }
                else if (!end_series1 && end_series2) {
                    take_from_1 = true;
                }
                else {
                    break;
                }

                if (take_from_1) {
                    *cur_out << val1 << ' ';

                    int temp;
                    if (f1 >> temp) {

                        if (temp < val1) {
                            end_series1 = true;
                        }
                        prev1 = val1;
                        val1 = temp;
                    } 
                    else {
                        have1 = false;
                        end_series1 = true;
                    }
                } 
                else {
                    *cur_out << val2 << ' ';
                    int temp;
                    if (f2 >> temp) {

                        if (temp < val2) {
                            end_series2 = true;
                        }
                        prev2 = val2;
                        val2 = temp;
                    } 
                    else {
                        have2 = false;
                        end_series2 = true;
                    }
                }

                if ((end_series1 || !have1) && (end_series2 || !have2)) {
                    stop_series = true;
                }
            }

            while (!end_series1 && have1) {
                *cur_out << val1 << ' ';
                int temp;

                if (f1 >> temp) {
                    if (temp < val1) {
                        break;
                    }
                    val1 = temp;
                } 
                else {
                    break;
                }
            }

            while (!end_series2 && have2) {
                *cur_out << val2 << ' ';
                int temp;

                if (f2 >> temp) {
                    if (temp < val2) {
                        break;
                    }
                    val2 = temp;
                } else {
                    break;
                }
            }

            cur_is_f3 = !cur_is_f3;
        }
        f1.close();
        f2.close();
        f3.close();
        f4.close();
        return series_out;
    }
}

void external_sort(string input, string output) {
    int series = distribution(input, "f1.txt", "f2.txt");

    if (series <= 0) {
        cerr << "Error" << endl;
        return;
    }

    if (series == 0) {
        ofstream out(output);
        out.close();
        return;
    }

    while (series > 1) {
        series = merge("f1.txt", "f2.txt", "f3.txt", "f4.txt");

        ifstream src3("f3.txt");
        ofstream dst1("f1.txt");
        int x;

        while (src3 >> x) {
            dst1 << x << ' ';
        }

        src3.close();
        dst1.close();

        ifstream src4("f4.txt");
        ofstream dst2("f2.txt");

        while (src4 >> x) {
            dst2 << x << ' ';
        }

        src4.close();
        dst2.close();
    }

  
    ifstream src("f1.txt");
    ofstream dst(output);
    int num;

    while (src >> num) {
        dst << num << ' ';
    }

    src.close();
    dst.close();
}

int main() {
    srand(time(0));

	int size, cur;
	string result = "result.txt", init = "init.txt", temp;
	ofstream data;
	ifstream res;

	cout << "Enter size: ";
	cin >> size;
	cout << "Before sorting: " << endl;

	data.open(init);
	for (int i = 0; i < size; i++) {
		cur = rand() % 100;
		cout << cur << " ";
		data << cur << "\n";
	}
	data.close();
	cout << endl << endl;

	external_sort("init.txt", "result.txt");

	cout << "After sorting: " << endl;
	res.open(result);

	for (int i = 0; i < size; i++) {
		res >> temp;
		cout << temp << " ";
	}
	res.close();
	cout << endl;

    return 0;
}