#ifndef PASSWORD_H
#define PASSWORD_H

class Password {
private:
  char* password;
  unsigned length;
  bool isDynamic;

  bool isInArray(char*, int, char); // utility function
public:
  class InvalidPassword {}; // thrown if password does not satisfy criteria
  class FileError {}; // throw when file i/o fails

  Password();
  Password(char*, unsigned);
  ~Password();

  unsigned getLength() { return length; }
  bool validate();
  void writePassword();
  void readPassword();
  void setPassword(char*, unsigned);
  bool isPassword(char*, unsigned);
};

#endif
