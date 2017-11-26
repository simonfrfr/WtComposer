
var api;

var widget ;
var lastelm;
var dragging;

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

function findCloserContainer(elem) {
    bIsContainer = false;
    if (elem !== null)
    {
        delem = elem.childNodes;
        for (i = 0; i < delem.length; i++){
            if (delem.class.compare("WContainerWidget") === 0 ||
                delem.class.compare("WAnchor"         ) === 0 ||
                delem.class.compare("WGroupBox"       ) === 0 ||
                delem.class.compare("WPanel"          ) === 0 ||
                delem.class.compare("WMenuItem"       ) === 0 ||
                delem.class.compare("WStackedWidget"  ) === 0 ||
                delem.class.compare("WTabItem"        ) === 0)
            {
                bIsContainer = true;
            }
        }

    }
    // if container return, else keep looking
    if (bIsContainer)
    {
        return elem;
    }
    else
    {
        if (!elem.parent().isNull())
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
