#include <iostream>
#include <vector>

template <typename T>
struct Neurons
{
    template <typename K>
    void connect(Neurons<K> &other);
};

struct Neuron : Neurons<Neuron>
{
    std::vector<Neuron *> in;
    std::vector<Neuron *> out;
    unsigned int ID;
    Neuron()
    {
        static int ID = 1;
        this->ID = ID++;
    }

    void add_in(Neuron *neuron)
    {
        in.push_back(neuron);
    }
    void add_out(Neuron *neuron)
    {
        out.push_back(neuron);
    }
    //like a vector...
    Neuron *begin() { return this; }
    Neuron *end() { return this + 1; }
};

struct NeuronLayer : std::vector<Neuron>, Neurons<NeuronLayer>
{
    NeuronLayer(int number_of_neurons)
    {
        while (number_of_neurons-- > 0)
            emplace_back(Neuron{});
    }
    void add_in(Neuron *neuron)
    {
        for (auto layer_neur = this->begin(); layer_neur != this->end(); layer_neur++)
        {
            layer_neur->add_in(neuron);
        }
    }
    void add_out(Neuron *neuron)
    {
        for (auto layer_neur = this->begin(); layer_neur != this->end(); layer_neur++)
        {
            layer_neur->add_out(neuron);
        }
    }
};

template <typename T>
template <typename K>
void Neurons<T>::connect(Neurons<K> &other)
{
    T &layer1 = static_cast<T &>(*this);
    K &layer2 = static_cast<K &>(other);

    for (auto neuron = layer1.begin(); neuron != layer1.end(); neuron++)
    {
        layer2.add_in(&(*neuron));
    }

    for (auto neuron = layer2.begin(); neuron != layer2.end(); neuron++)
    {
        layer1.add_out(&(*neuron));
    }
}

std::ostream &operator<<(std::ostream &console, Neuron &neuron)
{
    for (Neuron *n : neuron.in)
        console << n->ID << "\t>\t" << neuron.ID << "*"
                << "\n";
    for (Neuron *n : neuron.out)
        console << neuron.ID << "*\t>\t" << n->ID << "\n";
    return console;
}

std::ostream &operator<<(std::ostream &console, NeuronLayer &layer)
{
    for (auto neuron = layer.begin(); neuron != layer.end(); neuron++)
    {
        console << *neuron;
    }
    return console;
}

template <typename T>
std::ostream &operator<<(std::ostream &console, Neurons<T> &neurons)
{
    console << neurons;
    return console;
}

int main()
{
    Neuron single_neuron_1, single_neuron_2;
    NeuronLayer layer_1{1}, layer_2{2};

    single_neuron_1.connect(layer_1);
    layer_2.connect(single_neuron_2);
    layer_1.connect(layer_2);
    single_neuron_1.connect(single_neuron_2);

    std::cout << single_neuron_1 << "\n";
    std::cout << single_neuron_2 << "\n";
    std::cout << layer_1 << "\n";
    std::cout << layer_2 << "\n";
    return 0;
}

// EXPECTED OUTPUT
/*
1*	>	3
1*	>	2

4	>	2*
5	>	2*
1	>	2*

1	>	3*
3*	>	4
3*	>	5

3	>	4*
4*	>	2
3	>	5*
5*	>	2
*/