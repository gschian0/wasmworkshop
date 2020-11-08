/* Declares the wasmworkshop Audio Worklet Processor */

class wasmworkshop_AWP extends AudioWorkletGlobalScope.WAMProcessor
{
  constructor(options) {
    options = options || {}
    options.mod = AudioWorkletGlobalScope.WAM.wasmworkshop;
    super(options);
  }
}

registerProcessor("wasmworkshop", wasmworkshop_AWP);
