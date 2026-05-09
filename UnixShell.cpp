#include <bits/stdc++.h>
using namespace std;

class Directory {
public:
    string name;
    Directory* parent;
    unordered_map<string, unique_ptr<Directory>> children;

    Directory(string name, Directory* parent)
        : name(std::move(name)), parent(parent) {}

    Directory* getChild(const string& name) {
        auto it = children.find(name);
        return it == children.end() ? nullptr : it->second.get();
    }

    Directory* createChild(const string& name) {
        if (children.count(name)) return children[name].get();

        children[name] = make_unique<Directory>(name, this);
        return children[name].get();
    }
};

class FileSystem {
private:
    unique_ptr<Directory> root;
    Directory* cwd;

    vector<string> split(const string& path) {
        vector<string> parts;
        string token;

        for (char c : path) {
            if (c == '/') {
                if (!token.empty()) {
                    parts.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }

        if (!token.empty()) parts.push_back(token);
        return parts;
    }

    Directory* resolveWildcard(Directory* dir,
                               const vector<string>& parts,
                               int index) {
        if (!dir) return nullptr;
        if (index == parts.size()) return dir;

        const string& part = parts[index];

        if (part == ".") {
            return resolveWildcard(dir, parts, index + 1);
        }

        if (part == "..") {
            return resolveWildcard(dir->parent ? dir->parent : dir,
                                   parts,
                                   index + 1);
        }

        if (part == "*") {
            for (auto& [name, child] : dir->children) {
                Directory* result =
                    resolveWildcard(child.get(), parts, index + 1);

                if (result) return result;
            }

            return nullptr;
        }

        return resolveWildcard(dir->getChild(part), parts, index + 1);
    }

public:
    FileSystem() {
        root = make_unique<Directory>("", nullptr);
        cwd = root.get();
    }

    void mkdir(const string& path) {
        Directory* cur = path[0] == '/' ? root.get() : cwd;
        vector<string> parts = split(path);

        for (const string& part : parts) {
            if (part == "." || part == ".." || part == "*") {
                throw runtime_error("Invalid directory name: " + part);
            }

            cur = cur->createChild(part);
        }
    }

    void cd(const string& path) {
        Directory* start = path[0] == '/' ? root.get() : cwd;
        vector<string> parts = split(path);

        Directory* target = resolveWildcard(start, parts, 0);

        if (!target) {
            throw runtime_error("Path not found: " + path);
        }

        cwd = target;
    }

    string pwd() const {
        if (cwd == root.get()) return "/";

        vector<string> names;
        Directory* cur = cwd;

        while (cur != root.get()) {
            names.push_back(cur->name);
            cur = cur->parent;
        }

        reverse(names.begin(), names.end());

        string result;
        for (const string& name : names) {
            result += "/" + name;
        }

        return result;
    }
};

int main() {
    FileSystem fs;

    fs.mkdir("/home/gary/projects");
    fs.mkdir("/home/gary/docs");
    fs.mkdir("/tmp/test");

    cout << fs.pwd() << endl; // /

    fs.cd("/home/gary");
    cout << fs.pwd() << endl; // /home/gary

    fs.cd("*");
    cout << fs.pwd() << endl; // either /home/gary/projects or /home/gary/docs

    fs.cd("/");
    fs.cd("/home/*/projects");
    cout << fs.pwd() << endl; // /home/gary/projects
}
