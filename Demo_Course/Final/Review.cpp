class Base {

    friend void friendBase(Base* b);

/* A */
private:
    int priv;
    void privMethod(){
        priv = 0;
    }

/* B */
protected:
    int prot;
    void protMethod(){
        prot = 0;
    }

/* C */
public:
    int pub;
    void pubMethod(){
        pub = 0;
    }

};

class Derived : public Base {

    int derived;
    friend void friendDrived(Derived* d);

    /* D */
    void tryPrivDerived() {
        priv = 0; // would be an error
        privMethod();
    }

    /* E */
    void tryProtDerived() {
        prot = 0;
        protMethod();
    }

    /* F */
    void tryPubDerived() {
        pub = 0;
        pubMethod();
    }

};

class PrivateDerived : Base {}; // default: private inheritance, converting the public member to private, father class
class Rederived : PrivateDerived {
    /* G */
    void tryPubRederived(){
        pub = 0; // would be an error, public member of grandfather
        pubMethod();
    }
};


/* H */
void tryPrivOutside() {
    Derived d;
    d.priv = 0; // error
    d.privMethod();
}

/* I */
void tryProtOutside() {
    Derived d;
    d.prot = 0; // error
    d.protMethod();
}

/* J */
void tryPubOutside() {
    Derived d;
    d.pub = 0; // correct
    d.pubMethod();
}

friend void friendBase(Base* b){
    /* K */
    b->priv = 0;
    b->privMethod(); // correct
}

friend void friendDrived(Derived* d){ // friendship will not be inheritance
    /* L */
    d->derived = 0;
    d->tryPubDerived(); // correct

    /* M */
    d->priv = 0; // error
    d->privMethod();
}