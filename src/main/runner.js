
var api;

var widget ;
var lastelm;
var dragging;

var isNull = function(obj) {
  return obj == null;
}


function initialise() {
  if (typeof qt != 'undefined') new QWebChannel(qt.webChannelTransport, function(channel) {
    widget = channel.objects.mywebview;
      document.addEventListener('mousemove', function(e) {
          if (lastelm !== document.elementFromPoint(e.pageX, e.pageY)) {
              console.log(document.elementFromPoint(e.pageX, e.pageY));
              lastelm = document.elementFromPoint(e.pageX, e.pageY);
              widget.onHover(e.pageX, e.pageY);
          }
      })
  } );
}



function getCloserContainerId(){

}

function findCloserContainer(elem) {
    bIsContainer = widget.bIsContainer(elem);
    // if container return, else keep looking
    if (bIsContainer)
    {
        return elem.id;
    }
    else
    {
        if (!isNull(elem.parent()))
        {
            welemTemp = elem.parent();
            return findCloserContainer(welemTemp);
        }
        else
        {
            return null;
        }
    }
}


// this will work in IE 10, 11 and Safari/Chrome/Firefox/Edge
// add ES6 poly-fill for the Promise, if needed (or rewrite to use a callback)

let fetchStyle = function(url) {
  return new Promise((resolve, reject) => {
    let link = document.createElement('link');
    link.type = 'text/css';
    link.rel = 'stylesheet';
    link.onload = function() { resolve(); console.log('style has loaded'); };
    link.href = url;

    let headScript = document.querySelector('script');
    headScript.parentNode.insertBefore(link, headScript);
  });
};
