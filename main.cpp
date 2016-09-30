#include <sparrowhawk/normalizer.h>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#define PATH_MAX MAX_PATH
#else
#include <unistd.h>
#endif

using namespace std;

string cwd() {
    char buf[PATH_MAX];
    getcwd(buf, PATH_MAX);
    return string(buf);
}

int main(int argc, char **argv) {

    string af_dir = cwd();
    af_dir = af_dir.substr(0, af_dir.size() - 3) + "af/"; //remove 'bin' from the end and add 'af'

    speech::sparrowhawk::Normalizer normalizer;

    normalizer.Setup("sparrowhawk_configuration.ascii_proto", af_dir);

    string in = "I have 123 apples.";
    string out = "";

    normalizer.Normalize(in, &out);

    cout << "INPUT: " << in << endl;
    cout << "OUTPUT: " << out << endl;

    return 0;
}
