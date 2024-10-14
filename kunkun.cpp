  #include <iostream>

  class Chicken
  {
    private:
      int age = 24;
      char name[7] = "Kunkun";
    public:
      const char *getName() const  /// !
      {
        return name;    /// 这里做了自动类型转换。
      }
      void setAge(int _age)
      {
        age = _age;
      }
      int getAge()
      {
        return age;
      }
      Chicken(){};
      Chicken(int _age)
      {
        age = _age;
      }
      ~Chicken(){};
      void sing() {std::cout << "Chiken you are so beatiful!" << std::endl;}      
  };

  void show(Chicken &_c)  // 这里发生了什么？
  {
    std::cout << "Hi! Everyone, I'm " << _c.getName() << ", " << _c.getAge() << " years old." << std::endl;
  }
  
  int main()
  {
    Chicken kun;
    show(kun);
    return 0;
  }
