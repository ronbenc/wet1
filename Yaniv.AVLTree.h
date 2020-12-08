// //
// // Created by eilon on 24/04/2020.
// //
// /*

// AVLTree - a generic data type to store data using keys.

// * The following methods are available:

// * AVLTree                  - initialize an empty AVLTree

// * ~AVLTree                 - destroy an AVLTree (not to be used explicitly)

// * find                     - given an key, return the address of element associated with the key in the AVLTree

// * insert                   - given a key and element insert the element to the AVLTree, sorted by the key

// * remove                   - given a key, remove the element associated with the key from the AVLTree

// * isEmpty                  - returns weather the AVLTree is empty or not

// * inOrder                  - if given a limit and a counter,
//                             will iterate over only the specified amount of elements in the tree,
//                             from smallest largest (by '<' operator of key) and subject them to a generic action

// * inOrder                  - if no limit nor counter were applied,
//                             the function will iterate over all elements of the AVLTree
//                             from smallest to largest (by '<' operator of key) and subject them to a generic action




// ***   the methods parameters, requirements and return values

// ----------------------------------------------------------------------

// **  AVLTree() -

//  *    parameters: none
//  *    requirements: <typename Element, typename T>, the first to determine the values your AVLTree will be able to store,
//                     the second to determine by what type the tree will be sorted (the key type must provide '<','>','==' operators.
//  *    return value: an empty AVLTree in case of success, nullptr otherwise

// ----------------------------------------------------------------------

// **  ~AVLTree()
//  *    parameters: none
//  *    requirements: to be used only by the compiler
//  *    return value: none

//  ----------------------------------------------------------------------

// **  Element* find(const T& key); //returns null if not found
//  *    parameters: const T& key - the key indicating to element were searching
//  *    requirements: none
//  *    return value: if the key (along woth an element) was previously inserted to the AVLTree,
//                     a pointer to it's data, else - a nullptr

//  ----------------------------------------------------------------------

// **  AVLResult insert(const Element& element, const T& key);
//  *    parameters:   const Element& element - the element we want to store in the AVLTree
//                     const T& key - the key that determines where is the AVLTree the element will be stored
//  *    requirements: none
//  *    return values:    AVLSUCCESS - in case the element was successfully added,
//                         AVLFAILURE - in case the key was already inserted previously and not removed
//                         AVLALLOCATION_ERROR - in case of allocation error
//                         AVLINVALID_INPUT - in case the key or element are illegal

//  ----------------------------------------------------------------------

// **  AVLResult remove(const T& key);
//  *    parameters: const T& key - the key indicating to the element we wish to remove
//  *    requirements: none
//  *    return values:    AVLSUCCESS - in case the element was successfully removed,
//                         AVLFAILURE - in case the key is not in the AVLTree to begin with
//                         AVLALLOCATION_ERROR - in case of allocation error
//                         AVLINVALID_INPUT - in case the key is illegal

//  ----------------------------------------------------------------------

// **  bool isEmpty();
//  *    parameters: none
//  *    requirements: none
//  *    return values: true - if the AVLTree is empty, false otherwise

//  ----------------------------------------------------------------------

//     void inOrder(int& count, int finish, const Func& f);
//  *    parameters:   int& count - a counter, indicating how many elements were already subjected to the generic action
//                     int finish - a limit on how many elements we wish to subject to the generic action
//                     const Func& f - the generic action to to be subjected to the elements
//  *    requirements: (<typename Func>) the generic action must be implemented as a function object (that provide '()' operator)
//  *    return values: none

//  ----------------------------------------------------------------------

// **  void inOrder(const Func& f);
//  *    parameters:   const Func& f - the generic action to to be subjected to the elements
//  *    requirements: (<typename Func>) the generic action must be implemented as a function object (that provide '()' operator)
//  *    return values: none

//  ----------------------------------------------------------------------

// */


// #ifndef WET1_AVLTREE_H
// #define WET1_AVLTREE_H
// #include <iostream>
// #include <cassert>
// using namespace std;
// using std::ostream;

// typedef enum {
//     AVLSUCCESS = 0,
//     AVLFAILURE = -1,
//     AVLALLOCATION_ERROR = -2,
//     AVLINVALID_INPUT = -3,
// } AVLResult;

// template <typename Element, typename T>
// class AVLTree{
//     class Junction {
//     private:
//         T key;
//         Junction* parent = nullptr;
//         Junction* left = nullptr;
//         Junction* right = nullptr;
//         Element* element = new Element;
//         int height=0;
//     public:
//         explicit Junction(const Element& input,const T& k):
//         key(k) {
//             *element = input;
//         }
//         Junction (const Junction& other) = default;
//         ~Junction(){
//             delete element;
//         }
//         T Get_key(){
//             return key;
//         }
//         Element* Get_Element (){
//             return this->element;
//         }
//         void Set_Parent(Junction* j){
//             parent = j;
//         }
//         Junction* Get_Parent(){
//             return parent;
//         }
//         void Set_Left(Junction* j){
//             left = j;
//         }
//         Junction* Get_Left(){
//             return left;
//         }
//         void Set_Right(Junction* j){
//             right = j;
//         }
//         Junction* Get_Right(){
//             return right;
//         }
//         void Update_Height(){
//             int l, r;
//             if (left == nullptr){
//                 l = -1;
//             }
//             else{
//                 l = left->height;
//             }
//             if (right == nullptr){
//                 r = -1;
//             }
//             else{
//                 r = right->height;
//             }
//             height = max2(l,r)+1;
//         }
//         void Set_Height(int n){
//             height = n;
//         }
//         int Get_Height(){
//             return height;
//         }
//         int GetBalanceFactor(){
//             int l;
//             if (left == nullptr)
//                 l = -1;
//             else
//                 l = left->height;
//             int r;
//             if (right == nullptr)
//                 r = -1;
//             else
//                 r = right->height;
//             return l-r;
//         }
//         void Print() const { std::cout << element << std::endl; }


//     };     //the nodes of the tree

//     Junction* root;
//     Junction* smallest;
//     bool is_empty;

//     //methods for module's inside use - irrelevent to user
//     void AVLTreeDestroy(Junction* j){
//         if (j == nullptr){
//             return;
//         }
//         AVLTreeDestroy(j->Get_Left());
//         AVLTreeDestroy(j->Get_Right());
//         delete j;
//     }
//     Junction* RR_Roll(Junction* parent){
//         AVLTree<Element, T>::Junction* temp;
//         temp = parent->Get_Right();
//         parent->Set_Right(temp->Get_Left());
//         if (temp->Get_Left())
//             temp->Get_Left()->Set_Parent(parent);
//         temp->Set_Left(parent);
//         temp->Set_Parent(parent->Get_Parent());
//         if (parent->Get_Parent()){
//             parent == parent->Get_Parent()->Get_Left()?
//             parent->Get_Parent()->Set_Left(temp) : parent->Get_Parent()->Set_Right(temp);
//         }
//         parent->Set_Parent(temp);
//         parent->Update_Height();
//         temp->Update_Height();
//         return temp;
//     }
//     Junction* LL_Roll(Junction* parent){
//         AVLTree<Element, T>::Junction* temp;
//         temp = parent->Get_Left();
//         parent->Set_Left(temp->Get_Right());
//         if(temp->Get_Right())
//             temp->Get_Right()->Set_Parent(parent);
//         temp->Set_Right(parent);
//         temp->Set_Parent(parent->Get_Parent());
//         if (parent->Get_Parent()){
//             parent == parent->Get_Parent()->Get_Left()?
//             parent->Get_Parent()->Set_Left(temp) : parent->Get_Parent()->Set_Right(temp);
//         }
//         parent->Set_Parent(temp);
//         parent->Update_Height();
//         temp->Update_Height();
//         return temp;
//     }
//     Junction* LR_Roll(Junction* parent){
//         AVLTree<Element, T>::Junction* temp;
//         temp = parent->Get_Left();
//         AVLTree<Element, T>::Junction* temp2 = RR_Roll (temp);
//         parent->Set_Left(temp2);
//         temp2->Set_Parent(parent);
//         return LL_Roll (parent);
//     }
//     Junction* RL_Roll(Junction* parent){
//         AVLTree<Element, T>::Junction* temp;
//         temp = parent->Get_Right();
//         AVLTree<Element, T>::Junction* temp2 = LL_Roll (temp);
//         parent->Set_Right(temp2);
//         temp2->Set_Parent(parent);
//         return RR_Roll (parent);
//     }
//     Junction* Commence_Needed_Roll(Junction* temp){
//         Junction* top_after_roll = nullptr;
//         Junction* mem = temp;
//         if (temp->GetBalanceFactor() == 2){
//             if(temp->Get_Left()->GetBalanceFactor()>=0) {
//                 top_after_roll = LL_Roll(temp);
//             }
//             else if (temp->Get_Left()->GetBalanceFactor()==-1){
//                 top_after_roll = LR_Roll(temp);
//             }
//         }
//         else{ //temp->GetBalanceFactor() == -2
//             if(temp->Get_Right()->GetBalanceFactor()<=0){
//                 top_after_roll = RR_Roll(temp);
//             }
//             else if (temp->Get_Right()->GetBalanceFactor()==1){
//                 top_after_roll = RL_Roll(temp);
//             }
//         }
//         assert(top_after_roll!= nullptr);
//         if (root == mem) {
//             root = top_after_roll;
//         } else{
//             top_after_roll == top_after_roll->Get_Parent()->Get_Left()?
//             top_after_roll->Get_Parent()->Set_Left(top_after_roll) : top_after_roll->Get_Parent()->Set_Right(top_after_roll);

//         }
//         return top_after_roll;
//     }
//     Element* Find_s(Junction* j, T key){
//         if (j == nullptr){
//             return nullptr;
//         }
//         T temp = j->Get_key();
//         if (key == temp){
//             return j->Get_Element();
//         }
//         if (key > temp){
//             return Find_s(j->Get_Right(), key);
//         }
//         else{
//             return Find_s(j->Get_Left(), key);
//         }
//     }
//     Junction* Find_Junc(Junction* j, T key){
//         if (j == nullptr){
//             return nullptr;
//         }
//         T temp = j->Get_key();
//         if (key == temp){
//             return j;
//         }
//         if (key > temp){
//             return Find_Junc(j->Get_Right(), key);
//         }
//         else{
//             return Find_Junc(j->Get_Left(), key);
//         }
//     }
//     void Insert_bin(Junction* j, Junction* to_insert, T key){

//         if (key < j->Get_key()) {                                       //it's smaller than current so we'll check left
//             if (j->Get_Left()!= nullptr)                                // there is a left son
//                 Insert_bin(j->Get_Left(), to_insert, key);              //recursive call to the left
//             else {                                                      // it's smaller then than the smallest (on his branch)
//                 j->Set_Left(to_insert);
//                 to_insert->Set_Parent(j);
//             }
//         } else {                                                      //it's bigger than current so we'll check right
//             if (j->Get_Right()!= nullptr)                             // there is a right son
//                 Insert_bin(j->Get_Right(), to_insert, key);           //recursive call to the right
//             else {                                                    //it's bigger then than the biggest (on his branch)
//                 j->Set_Right(to_insert);
//                 to_insert->Set_Parent(j);
//             }
//         }
//     }
//     Junction* Remove_bin(Junction* to_remove){
//         //just a normal BINARY tree removal
//         Junction* to_return = to_remove->Get_Parent();                              //default value for leaves
//         if (to_remove->Get_Height() == 0) {                                         //no subtrees
//             if(root == to_remove){                                                  //last junction, also means to_return==null
//                 root = nullptr;
// //               we know that smallest == nullptr so we don't need to do it (because it happens by itself in smallest updating)
//             }
//             else{
//                 to_remove == to_remove->Get_Parent()->Get_Left()?                   //leaf
//                 to_remove->Get_Parent()->Set_Left(nullptr) : to_remove->Get_Parent()->Set_Right(nullptr);
//             }
//             delete to_remove;                                                       //calls de'tor
//             return to_return;
//         }
//         else if (to_remove->Get_Right() == nullptr) {                             //there's only a left subtree (which is a single leaf because the tree is balanced
//             to_remove->Get_Left()->Set_Parent(to_remove->Get_Parent());
//             if (to_remove->Get_Parent())
//                 to_remove == to_remove->Get_Parent()->Get_Left()?
//                 to_remove->Get_Parent()->Set_Left(to_remove->Get_Left()) : to_remove->Get_Parent()->Set_Right(to_remove->Get_Left());
//             if (root == to_remove) {
//                 root = root->Get_Left();
//             }
//             delete to_remove;                                                       //calls de'tor
//         }
//         else if (to_remove->Get_Left() == nullptr) {                             //there's only a right subtree (which is a single leaf because the tree is balanced
//             to_remove->Get_Right()->Set_Parent(to_remove->Get_Parent());
//             if (to_remove->Get_Parent())
//                 to_remove == to_remove->Get_Parent()->Get_Left()?
//                 to_remove->Get_Parent()->Set_Left(to_remove->Get_Right()) : to_remove->Get_Parent()->Set_Right(to_remove->Get_Right());
//             if (root == to_remove) {
//                 root = root->Get_Right();
//             }
//             delete to_remove;                                                       //calls de'tor
//         }
//         else {                                                                      //there are  both left and right subtrees - only right matters
//             Junction *successor = to_remove->Get_Right();
//             while (successor->Get_Left() != nullptr) {                              //get the next biggest after root, - there's no more left - o(log(n))
//                 successor = successor->Get_Left();
//             }

//             if (successor == to_remove->Get_Right()){
//                 to_return = successor;                                              //because to parent is going to be deleted (usually the next line - the else)
//                 if (successor->Get_Right() != nullptr) {                                //replacer is not a leaf - stitching is needed
//                     successor->Get_Right()->Set_Parent(successor->Get_Parent());
//                     successor->Get_Parent()->Set_Right(successor->Get_Right());
//                 }
//                 else //successor->Get_Right() == nullptr
//                     to_remove->Set_Right(nullptr);
//             }
//             else{ //successor != to_remove->Get_Right()
//                 to_return = successor->Get_Parent();                                //place to later start tests for miss-balanced junctions
//                 if (successor->Get_Right() != nullptr) {                                //replacer is not a leaf - stitching is needed
//                     successor->Get_Right()->Set_Parent(successor->Get_Parent());
//                     successor->Get_Parent()->Set_Left(successor->Get_Right());
//                 }
//                 else //successor->Get_Right() == nullptr
//                     successor->Get_Parent()->Set_Left(nullptr);
//             }

//             successor->Set_Parent(to_remove->Get_Parent());                         //replacing to_delete and successor
//             successor->Set_Left(to_remove->Get_Left());
//             successor->Set_Right(to_remove->Get_Right());
//             if (to_remove->Get_Left())
//                 to_remove->Get_Left()->Set_Parent(successor);
//             if (to_remove->Get_Right())
//                 to_remove->Get_Right()->Set_Parent(successor);
//             if (to_remove->Get_Parent()){
//                 to_remove == to_remove->Get_Parent()->Get_Left()?
//                 to_remove->Get_Parent()->Set_Left(successor) : to_remove->Get_Parent()->Set_Right(successor);
//             }
//             if (root == to_remove) {
//                 root = successor;
//             }
//             delete to_remove;
//         }
//         return to_return;
//     }
//     template <typename Func>
//     void InOrder_rec(Junction* j, const Func& f){
//         if (j == nullptr) {
//             return;
//         }
//         InOrder_rec(j->Get_Left(), f);             // roam left subtree
//         f(j->Get_Element());                       // do something
//         InOrder_rec(j->Get_Right(), f);            // roam right subtree
//     }
//     template <typename Func>
//     void InOrder_counted(Junction *j, int& count, int finish, const Func& f){

//         if (j == nullptr || count >= finish){
//             return;
//         }
//         f(j->Get_Element(), count);                                                    // do something
//         if (count == finish){
//             return;
//         }
//         InOrder_counted_rec(j->Get_Right(), count, finish, f);                  //the recursion assumption is that for a given j, its left subtree was already scanned
//         InOrder_counted(j->Get_Parent(), count, finish, f);                     //move one up and repeat
//     }
//     template <typename Func>
//     void InOrder_counted_rec(Junction *j, int& count,  int finish, const Func& f){

//         if (j == nullptr || count >= finish){
//             return;
//         }
//         InOrder_counted_rec(j->Get_Left(), count, finish, f);                     // roam left subtree
//         if (count == finish){
//             return;
//         }
//         f(j->Get_Element(), count);                                       // do something
//         if (count == finish){
//             return;
//         }
//         InOrder_counted_rec(j->Get_Right(), count, finish, f);                    // roam right subtree
//     }


// public:
//     explicit AVLTree(): root(nullptr), smallest(nullptr), is_empty(true) {}
//     ~AVLTree(){
//         AVLTreeDestroy(root);
//     }

//     Element* find(const T& key){

//         return Find_s(root, key);
//     }

//     AVLResult insert(const Element& element, const T& key){
//         if (find(key) != nullptr) {
//             return AVLFAILURE;
//         }
//         auto* new_junction = new Junction(element, key);
//         if ((smallest == nullptr) || (key < smallest->Get_key())){
//             smallest = new_junction;
//         }
//         if (root == nullptr) {
//             root = new_junction;
//             is_empty = false;
//             return AVLSUCCESS;
//         }
//         else {
//             Insert_bin(root, new_junction, key);
//             Junction* check = new_junction;
//             while (check != root) {                                                    //will iterate o(log(n)) times
//                 if (check->Get_Parent()->Get_Height() >= check->Get_Height() + 1) {    //BF of parent did not change - roll is not needed
//                     return AVLSUCCESS;
//                 }
//                 check->Get_Parent()->Set_Height(check->Get_Height() + 1);              //increase the height of junctions which height was affected along the route by 1
//                 if (check->Get_Parent()->GetBalanceFactor() == 2 || check->Get_Parent()->GetBalanceFactor() == -2){                 //a roll is needed
//                     Commence_Needed_Roll(check->Get_Parent());
//                     return AVLSUCCESS;                                                     //when inserting, if a single roll was done, the tree is balanced
//                 } else{
//                     check = check->Get_Parent();
//                 }
//             }
//         }
//         return AVLSUCCESS;
//     }

//     AVLResult remove(const T& key){

//         Junction* to_remove = Find_Junc(root, key);
//         if (to_remove == nullptr) {
//             return AVLFAILURE;
//         }
//         if (smallest == to_remove) {
//             if (smallest->Get_Right() != nullptr) { //means there's a right son
//                 smallest = to_remove->Get_Right(); //there's no other junctions because that would make the tree im-balanced
//             } else {
//                 smallest = to_remove->Get_Parent();
//             }
//         }
//         auto s = Remove_bin(to_remove);                                             //just a normal BINARY tree removal
//         if(s == nullptr){                                                           //tree is now empty
//             is_empty = true;
//             return AVLSUCCESS;
//         }
//         Junction* temp = s;
//         while (temp!= nullptr){                                                     //update heights along the search route, after normal binTree removal
//             temp->Update_Height();                                                  //-will iterate o(log(n)) times
//             temp = temp->Get_Parent();
//         }
//         Junction* v = nullptr;
//         while (s != nullptr) {                                                      //will iterate o(log(n)) times
//             if (s->GetBalanceFactor() == 2 || s->GetBalanceFactor() == -2) {        //means a roll is needed
//                 int old_height = s->Get_Height();
//                 v = Commence_Needed_Roll(s);
//                 s->Update_Height();
//                 if (s->Get_Height() == old_height) {                                   //height of subtree did not change - we're done
//                     return AVLSUCCESS;                                                     //when removing, we might need several rolls
//                 }
//                 else { //height of subtree which root is v changed and BF(v) is legal so continue the algorithm
//                     s=v;
//                 }
//             }
//             s = s->Get_Parent();
//         }
//         return AVLSUCCESS;
//     }
//     static int max2(int a, int b) {
//         return a>b? a:b;
//     }

//     bool isEmpty(){
//         if(root == nullptr) return true;
//         return false;
//     }
//     const Element* getRoot()
//     {
//         return root->Get_Element();
//     }

//     template<typename Func>
//     void inOrder(int& count, int finish, const Func& f){      //counted version of inOrder - will iterate over 'finish' amount of smallest key'd elements
//         if (finish<1){
//             return;
//         }
//         InOrder_counted(smallest, count, finish, f);
//     }

//     template<typename Func>     //goes through all
//     void inOrder(const Func& f){
//         InOrder_rec(root, f);
//     }


// };

// #endif //WET1_AVLTREE_H
