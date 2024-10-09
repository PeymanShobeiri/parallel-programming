#include <jni.h>
#include <simgrid/s4u.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

using namespace std;

void input_actor(simgrid::s4u::Mailbox* send_mailbox);
void transform_actor(simgrid::s4u::Mailbox* recv_mailbox);

// Declare external pointer to JavaVM
extern JavaVM* jvm;
simgrid::s4u::Mailbox* s2t_mailbox;
std::unique_ptr<simgrid::s4u::Engine> engine;

// Example spout actor function
void spout_actor_function() {
    // Spout logic here (e.g., emitting data)
    std::cout << "Spout is emitting data..." << std::endl;
}

// Example bolt actor function
void bolt_actor_function() {
    // Bolt logic here (e.g., processing received data)
    std::cout << "Bolt is processing data..." << std::endl;
}


JNIEXPORT jlong JNICALL Java_org_example_TopologyBuilder_init (JNIEnv *env, jobject obj) {
        int argc = 1;
        char *argv[] = {(char *)"simgrid_simulation"};
        engine = make_unique<simgrid::s4u::Engine>(&argc, argv);
        engine->load_platform("/home/peyman/Desktop/platform.xml");
        return reinterpret_cast <jlong> (engine.get());
}


JNIEXPORT void JNICALL Java_org_example_TopologyBuilder_createSpout (JNIEnv *env, jobject obj, jstring spoutName) {
    const char *spoutNameC = env->GetStringUTFChars(spoutName, NULL);

    s2t_mailbox = simgrid::s4u::Mailbox::by_name("spout_transform_mailbox");

    simgrid::s4u::Actor::create(spoutNameC, simgrid::s4u::Host::by_name("host"), input_actor, s2t_mailbox);
    env->ReleaseStringUTFChars(spoutName, spoutNameC);
}


JNIEXPORT void JNICALL Java_org_example_TopologyBuilder_createBolt (JNIEnv *env, jobject obj, jstring boltName) {
    const char *boltNameC = env->GetStringUTFChars(boltName, NULL);

    if (strcmp(boltNameC, "transform") == 0)
        simgrid::s4u::Actor::create("transform", simgrid::s4u::Host::by_name("host"), transform_actor, s2t_mailbox);

    env->ReleaseStringUTFChars(boltName, boltNameC);
}



JNIEXPORT void JNICALL Java_org_example_TopologyBuilder_submitTopologyNative (JNIEnv *env, jobject obj, jstring topologyName, jlong enginePtr) {
    simgrid::s4u::Engine* engineInstance = reinterpret_cast<simgrid::s4u::Engine*>(enginePtr);
        engineInstance->run();
}


// Native method implementation
//JNIEXPORT void JNICALL Java_org_example_TopologyBuilder_submitTopologyNative
//(JNIEnv *env, jobject obj, jstring topologyName, jobject spoutMap, jobject boltMap, jobject streamMap) {
  //  const char* topo_name = env->GetStringUTFChars(topologyName, 0);
   // std::cout << "Submitting topology: " << topo_name << std::endl;

    // Spout and Bolt handling
 //   jclass mapClass = env->FindClass("java/util/Map");
   // jmethodID entrySetMethod = env->GetMethodID(mapClass, "entrySet", "()Ljava/util/Set;");
   // jobject spoutEntrySet = env->CallObjectMethod(spoutMap, entrySetMethod);
 //   jobject boltEntrySet = env->CallObjectMethod(boltMap, entrySetMethod);
//
   // jclass setClass = env->FindClass("java/util/Set");
  //  jmethodID iteratorMethod = env->GetMethodID(setClass, "iterator", "()Ljava/util/Iterator;");
  //  jobject spoutIterator = env->CallObjectMethod(spoutEntrySet, iteratorMethod);
   // jobject boltIterator = env->CallObjectMethod(boltEntrySet, iteratorMethod);
//
  //  // Process Spouts
  //  while (env->CallBooleanMethod(spoutIterator, env->GetMethodID(env->FindClass("java/util/Iterator"), "hasNext", "()Z"))) {
   ///     jobject entry = env->CallObjectMethod(spoutIterator, env->GetMethodID(env->FindClass("java/util/Iterator"), "next", "()Ljava/lang/Object;"));
///
    ///    jclass entryClass = env->FindClass("java/util/Map$Entry");
      ///  jobject key = env->CallObjectMethod(entry, env->GetMethodID(entryClass, "getKey", "()Ljava/lang/Object;"));
       // const char* spoutName = env->GetStringUTFChars((jstring) key, 0);
       // std::cout << "Spout: " << spoutName << " added to topology." << std::endl;
//
 //       // Create SimGrid Actor for the spout
//	simgrid::s4u::Actor::create(spoutNameC, simgrid::s4u::Host::by_name("host"), input_actor, s2t_mailbox);
  //      simgrid::s4u::Actor::create(spoutName, spout_actor_function);
//
 //       env->ReleaseStringUTFChars((jstring) key, spoutName);
   // }

    // Process Bolts
  //  while (env->CallBooleanMethod(boltIterator, env->GetMethodID(env->FindClass("java/util/Iterator"), "hasNext", "()Z"))) {
   //     jobject entry = env->CallObjectMethod(boltIterator, env->GetMethodID(env->FindClass("java/util/Iterator"), "next", "()Ljava/lang/Object;"));
//
  //      jclass entryClass = env->FindClass("java/util/Map$Entry");
    //    jobject key = env->CallObjectMethod(entry, env->GetMethodID(entryClass, "getKey", "()Ljava/lang/Object;"));
    //    const char* boltName = env->GetStringUTFChars((jstring) key, 0);
     //   std::cout << "Bolt: " << boltName << " added to topology." << std::endl;
//
    //    // Create SimGrid Actor for the bolt
  //      simgrid::s4u::Actor::create(boltName, bolt_actor_function);
//
      //  env->ReleaseStringUTFChars((jstring) key, boltName);
  ///  }
//
 ///   // Stream handling can be added here, connecting spouts and bolts
//
 //   env->ReleaseStringUTFChars(topologyName, topo_name);/
//}
void input_actor(simgrid::s4u::Mailbox* send_mailbox) {
    for (int i = 1; i <= 10; ++i) {
        std::cout << "Spout is sending: " << i << "\n";
        send_mailbox->put(new double(i), sizeof(double));
    }
    send_mailbox->put(new double(-1.0), sizeof(double));
}

void transform_actor(simgrid::s4u::Mailbox* recv_mailbox) {
    while (true) {
        double* message_ptr = recv_mailbox->get<double>();
        if (*message_ptr == -1.0) {
            cout << "End of transform\n";
            delete message_ptr;
            break;
        }
        double transformed_message = (*message_ptr) * 2.0;
        std::cout << "Transform received: " << *message_ptr << ", sending: " << transformed_message << "\n";
        delete message_ptr;
    }
}
