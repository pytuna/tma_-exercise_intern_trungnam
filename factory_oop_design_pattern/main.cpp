#include<iostream>
#include<memory>
class Person {
 public:
  virtual ~Person() {}
  virtual std::string Operation() const = 0;
};

class Student : public Person {
 public:
  std::string Operation() const override {
    return "{Học sinh}";
  }
};
class Teacher : public Person {
 public:
  std::string Operation() const override {
    return "{Giáo viên}";
  }
};

class Creator {

 public:
  virtual ~Creator(){};
  virtual Person* FactoryMethod() const = 0;
  

  std::string SomeOperation() const {
    
    Person* person = this->FactoryMethod();
    
    std::string result = "Factory Method tạo: " + person->Operation();
    delete person;
    return result;
  }
};


class ConcreteStudent : public Creator {

 public:
  Person* FactoryMethod() const override {
    return new Student();
  }
};

class ConcreteTeacher : public Creator {
 public:
  Person* FactoryMethod() const override {
    return new Teacher();
  }
};


void ClientCode(const Creator& creator) {
  std::cout << "Code Client:\n"
            << creator.SomeOperation() << std::endl;
}

int main() {
  std::unique_ptr<Creator> creator1(new ConcreteStudent());
  ClientCode(*creator1);
  std::cout << std::endl;
  Creator* creator2 = new ConcreteTeacher();
  ClientCode(*creator2);
  delete creator2;
  return 0;
}