
#ifndef IOGUIEFFECTLISTENER_H
#define IOGUIEFFECTLISTENER_H

class OguiEffectEvent;

class IOguiEffectListener
{
public:
	virtual ~IOguiEffectListener() {}
  // all in one
  virtual void EffectEvent(OguiEffectEvent *eve) = 0;
};

#endif
